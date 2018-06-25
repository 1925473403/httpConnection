class Integer {
    Integer();
    Integer(const Integer &);
    Integer& operator=(const Integer &);
    public:
        static int parseInt(const char *str) {
            int x = 0;
            if (str != NULL) {
                x = atoi(str);
            }
            return x;
        }
        static std::string toString(const int x) {
            char str[128] = { 0 };
            snprintf(str, 127, "%d", x);
            return std::string(str);
        }
};
