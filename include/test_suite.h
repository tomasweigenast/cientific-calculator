struct TestSuite {
    public:
        TestSuite(const TestSuite&) = delete;
        TestSuite() {}

        void run();
};