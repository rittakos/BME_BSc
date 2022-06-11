


class Singleton {

    private:


        Singleton() {

        }

    public:

        static Singleton& getInstance() {
            static Singleton s;
            return s;
        }

        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;
        Singleton(Singleton&&) = delete;
        Singleton& operator=(Singleton&&) = delete;

};