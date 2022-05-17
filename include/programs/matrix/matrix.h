#include <iostream>
#include <iomanip>
#include <vector>
#include <util/id_generator.h>
#include <parser_exception/program_error.h>

struct  Matrix {
    private:
        unsigned int m_RowCount;
        unsigned int m_ColumnCount;
        double** m_Matrix;
        bool m_Empty;
        std::string m_Id;

        void initialize_() {
            m_Matrix = new double*[m_RowCount];
            for(unsigned int i = 0; i < m_RowCount; i++) {
                m_Matrix[i] = new double[m_ColumnCount];
            }
        }

    public:
        Matrix() = delete;
        Matrix(const Matrix& other) : m_RowCount(other.m_RowCount), m_ColumnCount(other.m_ColumnCount), m_Empty(other.m_Empty), m_Id(random_id()) {
            initialize_();
            for(uint i = 0; i < other.m_RowCount; i++) {
                for(uint j = 0; j < other.m_ColumnCount; j++) {
                    double value = other.m_Matrix[i][j];
                    this->m_Matrix[i][j] = value;
                }
            }
        }
        Matrix(unsigned int rowCount, unsigned int columnCount) : m_RowCount(rowCount), m_ColumnCount(columnCount), m_Empty(true), m_Id(random_id()) {
            initialize_();
            std::cout << "[DEBUG] Created matrix with id " << m_Id << std::endl;
        }
        Matrix(const std::vector<std::vector<double>>& rows, unsigned int columnCount) : m_RowCount(rows.size()), m_ColumnCount(columnCount), m_Empty(false), m_Id(random_id()) {
            uint i = 0;
            for(std::vector<double> cols : rows) 
            {
                m_Matrix[i] = new double[cols.size()];
                uint j = 0;
                for(double value : cols) {
                    m_Matrix[i][j] = value;
                    j++;
                }

                i++;
            }

            std::cout << "[DEBUG] Created matrix with id " << m_Id << std::endl;
        }
        ~Matrix() {
            for(unsigned int i = 0; i < m_RowCount; ++i) {
                delete[] m_Matrix[i];
            }

            delete[] m_Matrix;

            std::cout << "[DEBUG] Deleted matrix: " << m_Id << std::endl;
        }

        unsigned int row_count() const;
        unsigned int column_count() const;
        bool is_empty() const;
        bool is_identity() const;
        void set(unsigned int i, unsigned int j, double value);
        double at(unsigned int i, unsigned int j) const;
        double sum() const;
        Matrix main_diagonal();
        Matrix secondary_diagonal();
        Matrix transpose();

        static Matrix identity(unsigned int rowCount, unsigned int columnCount);
        static Matrix zero(unsigned int rowCount, unsigned int columnCount);

        friend std::ostream& operator<<(std::ostream& stream, const Matrix& m) 
        {

            if(m.m_Empty) 
            {
                stream << "---- Matrix(" << m.m_RowCount << "x" << m.m_ColumnCount << ") ----" << std::endl;
                stream << "Empty matrix." << std::endl;
                stream << "------------------" << std::endl;
            }
            else
            {

                int width = 0;
                /* compute the required width */
                for (size_t i = 0; i < m.m_RowCount; i++) {
                    for (size_t j = 0; j < m.m_ColumnCount; j++) {
                        int w = snprintf(NULL, 0, "%.2f", m.m_Matrix[i][j]);
                        if (width < w) {
                            width = w;
                        }
                    }
                }

                stream << std::endl << "Matrix(" << m.m_RowCount << "x" << m.m_ColumnCount << "):" << std::endl;
                for (size_t i = 0; i < m.m_RowCount; i++) {
                    stream << "[";
                    for (size_t j = 0; j < m.m_ColumnCount; j++) {
                        if (j != 0) {
                            stream << ", ";
                        }

                        printf("%*.2f", width, m.m_Matrix[i][j]);
                    }

                    stream << "]" << std::endl;
                }
            }

            return stream;
        } 
};

  