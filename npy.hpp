#include <complex>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdint>
#include <vector>
#include <endian.h>
#include <typeinfo>
#include <stdexcept>

namespace npy {

const char magic_string = "\x93NUMPY";
const size_t magic_string_length = 6;

inline void magic(std::ostream& ostream, unsigned char v_major=1, unsigned char v_minor=0) {
  ostream.write(magic_string, magic_string_length);
  ostream.put(v_major);
  ostream.put(v_minor);
}

inline void read_magic(std::istream& istream, unsigned char *v_major, unsigned char *v_minor) {
  char *buf = new char[magic_string_length+2];
  istream.read(buf, magic_string_length+2);

  for (size_t i=0; i < magic_string_length; i++) {
    if(preamble[i] != magic_string[i]) {
      throw std::runtime_error("io error: this file do not have a valid npy format.");
    }
  }

  *v_major = buf[magic_string_length];
  *v_minor = buf[magic_string_length+1];
  delete[] buf;
}

inline std::string map_type(const std::type_info& t)
{
    if(t == typeid(float) ) return "f" + std::to_string(sizeof(float));
    if(t == typeid(double) ) return "f" + std::to_string(sizeof(double));
    if(t == typeid(long double) ) return "f" + std::to_string(sizeof(long double));

    if(t == typeid(int) ) return "i" + std::to_string(sizeof(int));
    if(t == typeid(char) ) return "i" + std::to_string(sizeof(char));
    if(t == typeid(short) ) return "i" + std::to_string(sizeof(short));
    if(t == typeid(long) ) return "i" + std::to_string(sizeof(long));
    if(t == typeid(long long) ) return "i" + std::to_string(sizeof(long long));

    if(t == typeid(unsigned char) ) return "u" + std::to_string(sizeof(unsigned char));
    if(t == typeid(unsigned short) ) return "u" + std::to_string(sizeof(unsigned short));
    if(t == typeid(unsigned long) ) return "u" + std::to_string(sizeof(unsigned long));
    if(t == typeid(unsigned long long) ) return "u" + std::to_string(sizeof(unsigned long long));
    if(t == typeid(unsigned int) ) return "u" + std::to_string(sizeof(unsigned int));

    if(t == typeid(std::complex<float>) ) return "c" + std::to_string(sizeof(std::complex<float>));
    if(t == typeid(std::complex<double>) ) return "c" + std::to_string(sizeof(std::complex<double>));
    if(t == typeid(std::complex<long double>) ) return "c" + std::to_string(sizeof(std::complex<long double>));

    throw std::runtime_error("invalid data type");
}

inline std::string get_typestring(const std::type_info& t) {
    std::ostringstream ss;
    // little endian or big endian?
    if (isle())
      ss << "<";
    else
      ss << ">";

    // data type and word size
    if(t == typeid(float) ) { ss << "f" << sizeof(float);  return ss.str(); }
    if(t == typeid(double) ) { ss << "f" << sizeof(double);  return ss.str(); }
    if(t == typeid(long double) ) { ss << "f" << sizeof(long double);  return ss.str(); }

    if(t == typeid(char) ) { ss << "i" << sizeof(char);  return ss.str(); }
    if(t == typeid(short) ) { ss << "i" << sizeof(short);  return ss.str(); }
    if(t == typeid(int) ) { ss << "i" << sizeof(int);  return ss.str(); }
    if(t == typeid(long) ) { ss << "i" << sizeof(long);  return ss.str(); }
    if(t == typeid(long long) ) { ss << "i" << sizeof(long long);  return ss.str(); }

    if(t == typeid(unsigned char) ) { ss << "u" << sizeof(unsigned char);  return ss.str(); }
    if(t == typeid(unsigned short) ) { ss << "u" << sizeof(unsigned short);  return ss.str(); }
    if(t == typeid(unsigned int) ) { ss << "u" << sizeof(unsigned int);  return ss.str(); }
    if(t == typeid(unsigned long) ) { ss << "u" << sizeof(unsigned long);  return ss.str(); }
    if(t == typeid(unsigned long long) ) { ss << "u" << sizeof(unsigned long long);  return ss.str(); }

    if(t == typeid(std::complex<float>) ) { ss << "c" << sizeof(std::complex<float>);  return ss.str(); }
    if(t == typeid(std::complex<double>) ) { ss << "c" << sizeof(std::complex<double>);  return ss.str(); }
    if(t == typeid(std::complex<long double>) ) { ss << "c" << sizeof(std::complex<long double>);  return ss.str(); }

    throw std::runtime_error("unsupported data type");
}


// check if host is little endian
inline bool isle(void) {
  unsigned int i = 1;
  char *c = (char*)&i;
  if (*c)
    return true;
  else
    return false;
}

inline std::string trim_s(std::string s, const char * c){
  size_t start_pos, end_pos, len;
  start_pos = s.find_first_not_of(c);
  end_pos = s.find_last_not_of(c);
  if (start_pos == std::string::npos )
    start_pos = 0;
  if (end_pos == std::string::npos )
    len = std::string::npos;
  else
    len = end_pos - start_pos + 1;

  return s.substr(start_pos, len);
}

inline std::string unwrap_s(std::string s, char delim_front, char delim_back) {
  std::string str = trim_s(s, " ");
  if ((str.back() == delim_back) && (str.front() == delim_front))
    return str.substr(1, str.length()-2);
  else
    throw std::runtime_error("unable to unwrap");
}

inline std::string get_value_from_map(std::string mapstr) {
  std::string str = trim_s(mapstr, " ");
  size_t sep_pos = str.find_first_of(":");
  if (sep_pos == std::string::npos || sep_pos >= str.length())
    return "";

  str = str.substr(sep_pos+1);
  return trim_s(str, " ");
}

inline void pop_char(std::string& s, char c) {
  if (s.back() == c)
    s.pop_back();
}

inline void ParseHeader(std::string header, std::string& descr, bool *fortran_order, std::vector<unsigned long>& shape) {
  /*
     The first 6 bytes are a magic string: exactly "x93NUMPY".

     The next 1 byte is an unsigned byte: the major version number of the file format, e.g. x01.

     The next 1 byte is an unsigned byte: the minor version number of the file format, e.g. x00. Note: the version of the file format is not tied to the version of the numpy package.

     The next 2 bytes form a little-endian unsigned short int: the length of the header data HEADER_LEN.

     The next HEADER_LEN bytes form the header data describing the array's format. It is an ASCII string which contains a Python literal expression of a dictionary. It is terminated by a newline ('n') and padded with spaces ('x20') to make the total length of the magic string + 4 + HEADER_LEN be evenly divisible by 16 for alignment purposes.

     The dictionary contains three keys:

     "descr" : dtype.descr
     An object that can be passed as an argument to the numpy.dtype() constructor to create the array's dtype.
     "fortran_order" : bool
     Whether the array data is Fortran-contiguous or not. Since Fortran-contiguous arrays are a common form of non-C-contiguity, we allow them to be written directly to disk for efficiency.
     "shape" : tuple of int
     The shape of the array.
     For repeatability and readability, this dictionary is formatted using pprint.pformat() so the keys are in alphabetic order.
   */

  // remove trailing newline
  if (header.back() != '\n')
    throw std::runtime_error("invalid header");
  header.pop_back();

  // remove padding
  std::string s = trim_s(header, " ");

  // unwrap dictionary and remove whitespaces
  s = unwrap_s(s, '{', '}');
  s = trim_s(s, " ");

  // find the positions of the 3 dictionary keys
  size_t keypos_descr = s.find("'descr'");
  size_t keypos_fortran = s.find("'fortran_order'");
  size_t keypos_shape = s.find("'shape'");

  // make sure the keys are present
  if (keypos_descr == std::string::npos)
    throw std::runtime_error("missing 'descr' key");
  if (keypos_fortran == std::string::npos)
    throw std::runtime_error("missing 'fortran_order' key");
  if (keypos_shape == std::string::npos)
    throw std::runtime_error("missing 'shape' key");

  // make sure the keys are in order
  if (keypos_descr >= keypos_fortran || keypos_fortran >= keypos_shape)
    throw std::runtime_error("header keys in wrong order");

  // get the 3 key-value pairs
  std::string keyvalue_descr;
  keyvalue_descr = s.substr(keypos_descr, keypos_fortran - keypos_descr);
  keyvalue_descr = trim_s(keyvalue_descr, " ");
  pop_char(keyvalue_descr, ',');

  std::string keyvalue_fortran;
  keyvalue_fortran = s.substr(keypos_fortran, keypos_shape - keypos_fortran);
  keyvalue_fortran = trim_s(keyvalue_fortran, " ");
  pop_char(keyvalue_fortran, ',');

  std::string keyvalue_shape;
  keyvalue_shape = s.substr(keypos_shape, std::string::npos);
  keyvalue_shape = trim_s(keyvalue_shape, " ");
  pop_char(keyvalue_shape, ',');

  // get the values (right side of `:')
  std::string descr_s = get_value_from_map(keyvalue_descr);
  std::string fortran_s = get_value_from_map(keyvalue_fortran);
  std::string shape_s = get_value_from_map(keyvalue_shape);

  /* 
     TODO: this is where it gets messy. descr can be really complicated
     we just ignore that fact and hope we only encounter simple ones
  */
  descr = unwrap_s(descr_s, '\'', '\'');

  // convert literal Python bool to C++ bool
  if (fortran_s == "True")
    *fortran_order = true;
  else if (fortran_s == "False")
    *fortran_order = false;
  else
    throw std::runtime_error("invalid fortran_order value");

  // parse the shape Python tuple ( x, y, z,)

  // first clear the vector
  shape.clear();
  shape_s = unwrap_s(shape_s, '(', ')');

  // a tokenizer would be nice... 
  size_t pos = 0;
  size_t pos_next;
  for(;;) {
    pos_next = shape_s.find_first_of(',', pos);
    std::string dim_s;
    if (pos_next != std::string::npos)
      dim_s = shape_s.substr(pos, pos_next - pos);
    else
      dim_s = shape_s.substr(pos);
    pop_char(dim_s, ',');
    dim_s = trim_s(dim_s, " ");
    if (dim_s.length() == 0) {
      if (pos_next != std::string::npos)
        throw std::runtime_error("invalid shape");
    }else{
      std::stringstream ss;
      ss << dim_s;
      unsigned long tmp;
      ss >> tmp;
      shape.push_back(tmp);
    }
    if (pos_next != std::string::npos)
      pos = ++pos_next;
    else
      break;
  }
}

inline void WriteHeader(std::ostream& out, const std::string& descr, bool fortran_order, unsigned int n_dims, const unsigned long shape[])
{
    std::ostringstream ss_header;
    std::string s_fortran_order;
    if (fortran_order)
      s_fortran_order = "True";
    else
      s_fortran_order = "False";

    std::ostringstream ss_shape;
    ss_shape << "(";
    for (unsigned int n=0; n < n_dims; n++){
      ss_shape << shape[n] << ", ";
    }
    ss_shape << ")";

    ss_header << "{'descr': '" << descr << "', 'fortran_order': " << s_fortran_order << ", 'shape': " << ss_shape.str() << " }";

    size_t header_len = ss_header.str().length() + 1;
    size_t metadata_len = header_len + magic_string_length + 2;

    unsigned char version[2] = {1, 0};
    if (metadata_len >= 255*255) {
      metadata_len = header_len + magic_string_length + 4;
      version = {2, 0};
    }
    size_t padding_len = (16-metadata_len) % 16;
    std::string padding (padding_len, ' ');
    ss_header << padding;
    ss_header << '\n';

    std::string header = ss_header.str();
    size_t header_len = s_dictionary.length() + padding.length() + 1;

    // write magic
    write_magic(out, version[0], version[1]);

    // write header length
    if (version[0] == 1 && version[2] == 0) {
      uint16_t header_len_le16 = htole16(header.length());
      out.write(reinterpret_cast<char *> &header_len_le16, 2);
    }else{
      uint32_t header_len_le32 = htole32(header.length());
      out.write(reinterpret_cast<char *> &header_len_le32, 4);
    }

    out << header;
}

template<typename Scalar>
void SaveArrayAsNumpy( const std::string& filename, bool fortran_order, unsigned int n_dims, const unsigned long shape[], const std::vector<Scalar>& data)
{
    std::string typestring = get_typestring(typeid(Scalar));

    std::ofstream stream( filename, std::ofstream::binary);
    if(!stream) {
        throw std::runtime_error("io error: failed to open a file.");
    }
    WriteHeader(stream, typestring, fortran_order, n_dims, shape);

    size_t size = 1;
    for (unsigned int i=0; i<n_dims; ++i)
      size *= shape[i];
    stream.write(reinterpret_cast<const char*>(&data[0]), sizeof(Scalar) * size);
}

std::string read_header_1_0(std::istream istream) {
    // read header length and convert from little endian
    uint16_t header_length_raw;
    char *header_ptr = reinterpret_cast<char *>(&header_length_raw);
    stream.read(header_ptr, 2);
    uint16_t header_length = le16toh(header_length_raw);

    if((magic_string_length + 2 + 2 + header_length) % 16 != 0) {
        // display warning
    }

    char *buf = new char[header_length];
    stream.read(buf, header_length);
    std::string header (buf);
    delete[] buf;

    return header;
}

std::string read_header_2_0(std::istream istream) {
    // read header length and convert from little endian
    uint32_t header_length_raw;
    char *header_ptr = reinterpret_cast<char *>(&header_length_raw);
    stream.read(header_ptr, 4);
    uint32_t header_length = le32toh(header_length_raw);

    if((magic_string_length + 2 + 4 + header_length) % 16 != 0) {
      // display warning
    }

    char *buf = new char[header_length];
    stream.read(buf, header_length);
    std::string header (buf);
    delete[] buf;

    return header;
}

template<typename Scalar>
void LoadArrayFromNumpy(const std::string& filename, std::vector<unsigned long>& shape, std::vector<Scalar>& data)
{
    std::ifstream stream(filename, std::ifstream::binary);
    if(!stream) {
        throw std::runtime_error("io error: failed to open a file.");
    }
    // check magic bytes an version number
    unsigned char v_major, v_minor;
    read_magic(stream, &v_major, &v_minor);

    std::string header;

    if(v_major == 1 && v_minor == 0){
      header = read_header_1_0(stream);
    }else if(v_major == 2 && v_minor == 0) {
      header = read_header_2_0(stream);
    }else{
       throw std::runtime_error("unsupported file format version");
    }

    // parse header
    bool fortran_order;
    std::string typestr;

    ParseHeader(header, typestr, &fortran_order, shape);

    /* check the typestring
       this is a mess! numpy supports *really* complex typestrings.
       we do not
    */
    std::string expect_descr = get_typestring(typeid(Scalar));
    if (descr != expect_descr) {
      throw std::runtime_error("formatting error: typestrings not matching");
    }

    // compute the data size based on the shape
    size_t total_size = 1;
    for(size_t i=0; i<shape.size(); ++i) {
        total_size *= shape[i];
    }
    data.resize(total_size);

    // read the data
    stream.read(reinterpret_cast<char*>(&data[0]), sizeof(Scalar)*total_size);
}

} // namespace npy
