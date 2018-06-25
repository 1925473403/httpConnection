#include <string>
#include "HTTP.h"
using namespace std;
int HTTP::CR = 13; // <US-ASCII CR, carriage return (13)>
int HTTP::LF = 10; // <US-ASCII LF, linefeed (10)>
int HTTP::SP = 32; // <US-ASCII SP, space (32)>
int HTTP::HT = 9;  // <US-ASCII HT, horizontal-tab (9)>

/** HTTP header definitions */
std::string HTTP::TRANSFER_ENCODING = "Transfer-Encoding";
std::string HTTP::CONTENT_LEN  = "Content-Length";
std::string HTTP::CONTENT_TYPE = "Content-Type";
std::string HTTP::CONTENT_ENCODING = "Content-Encoding";
std::string HTTP::EXPECT_DIRECTIVE = "Expect";
std::string HTTP::CONN_DIRECTIVE = "Connection";
std::string HTTP::TARGET_HOST = "Host";
std::string HTTP::USER_AGENT = "User-Agent";
std::string HTTP::DATE_HEADER = "Date";
std::string HTTP::SERVER_HEADER = "Server";

/** HTTP expectations */
std::string HTTP::EXPECT_CONTINUE = "100-continue";

/** HTTP connection control */
std::string HTTP::CONN_CLOSE = "Close";
std::string HTTP::CONN_KEEP_ALIVE = "Keep-Alive";

/** Transfer encoding definitions */
std::string HTTP::CHUNK_CODING = "chunked";
std::string HTTP::IDENTITY_CODING = "identity";

/** Common charset definitions */
std::string HTTP::UTF_8 = "UTF-8";
std::string HTTP::UTF_16 = "UTF-16";
std::string HTTP::US_ASCII = "US-ASCII";
std::string HTTP::ASCII = "ASCII";
std::string HTTP::ISO_8859_1 = "ISO-8859-1";

/** Default charsets */
std::string HTTP::DEFAULT_CONTENT_CHARSET = ISO_8859_1;
std::string HTTP::DEFAULT_PROTOCOL_CHARSET = US_ASCII;

/** Content type definitions */
std::string HTTP::OCTET_STREAM_TYPE = "application/octet-stream";
std::string HTTP::PLAIN_TEXT_TYPE = "text/plain";
std::string HTTP::CHARSET_PARAM = "; charset=";

/** Default content type */
std::string HTTP::DEFAULT_CONTENT_TYPE = OCTET_STREAM_TYPE;
