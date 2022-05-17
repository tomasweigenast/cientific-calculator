struct Pos 
{
    private:
        unsigned int m_i;
        unsigned int m_j;

    public:
        Pos() = delete;
        Pos(const Pos& other) : m_i(other.m_i), m_j(other.m_j) {}
        Pos(unsigned int i, unsigned int j) : m_i(i), m_j(j) {}

        unsigned int get_i();
        unsigned int get_j();

        void set_i(unsigned int i);
        void set_j(unsigned int j);
        void set(unsigned int i, unsigned int j);
};