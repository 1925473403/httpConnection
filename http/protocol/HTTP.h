class HTTP {
    private:
        HTTP() {}
    public:
        static int CR ;
        static int LF ;
        static int SP ;
        static int HT ;
    
        /** HTTP header definitions */
        static std::string TRANSFER_ENCODING ;
        static std::string CONTENT_LEN  ;
        static std::string CONTENT_TYPE ;
        static std::string CONTENT_ENCODING ;
        static std::string EXPECT_DIRECTIVE ;
        static std::string CONN_DIRECTIVE ;
        static std::string TARGET_HOST ;
        static std::string USER_AGENT ;
        static std::string DATE_HEADER ;
        static std::string SERVER_HEADER ;
    
        /** HTTP expectations */
        static std::string EXPECT_CONTINUE ;
        /** HTTP connection control */
        static std::string CONN_CLOSE ;
        static std::string CONN_KEEP_ALIVE ;
    
        /** Transfer encoding definitions */
        static std::string CHUNK_CODING ;
        static std::string IDENTITY_CODING ;
    
        /** Common charset definitions */
        static std::string UTF_8 ;
        static std::string UTF_16 ;
        static std::string US_ASCII ;
        static std::string ASCII ;
        static std::string ISO_8859_1 ;
    
        /** Default charsets */
        static std::string DEFAULT_CONTENT_CHARSET ;
        static std::string DEFAULT_PROTOCOL_CHARSET ;
    
        /** Content type definitions */
        static std::string OCTET_STREAM_TYPE ;
        static std::string PLAIN_TEXT_TYPE ;
        static std::string CHARSET_PARAM ;
    
        /** Default content type */
        static std::string DEFAULT_CONTENT_TYPE ;
    
        static bool isWhitespace(char ch) {
            return ch == SP || ch == HT || ch == CR || ch == LF;
        }
};
