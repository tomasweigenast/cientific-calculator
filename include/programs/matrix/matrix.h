#include <iostream>
#include <vector>
#include <parser_exception/program_error.h>

struct  Matrix {
    private:
        unsigned int m_RowCount;
        unsigned int m_ColumnCount;
        double** m_Matrix;

        void initialize_() {
            m_Matrix = new double*[m_RowCount];
            for(unsigned int i = 0; i < m_RowCount; i++) {
                m_Matrix[i] = new double[m_ColumnCount];
            }
        }

    public:
        // Matrix() = delete;
        Matrix(unsigned int rowCount, unsigned int columnCount) : m_RowCount(rowCount), m_ColumnCount(columnCount) {
            initialize_();
        }
        Matrix(const std::vector<std::vector<double>>& rows, unsigned int columnCount) : m_RowCount(rows.size()), m_ColumnCount(columnCount) {
            unsigned int i = 0;
            for(std::vector<double> cols : rows) 
            {
                if(i == columnCount) {
                    throw ProgramException("The amount of column values is not " + columnCount);
                }

                m_Matrix[i] = cols.data();
                i++;
            }
        }
        ~Matrix() {
            for(unsigned int i = 0; i < m_RowCount; ++i) {
                delete[] m_Matrix[i];
            }

            delete[] m_Matrix;

            std::cout << "Matrix deleted." << std::endl;
        }

        unsigned int row_count() const;
        unsigned int column_count() const;
        void set(unsigned int i, unsigned int j, double value);
        double at(unsigned int i, unsigned int j) const;

        static Matrix identity(unsigned int rowCount, unsigned int columnCount); 

        friend std::ostream& operator<<(std::ostream& stream, const Matrix& m) 
        {
            for(unsigned int i = 0; i < m.m_RowCount; i++) 
            {
                stream << "[";
                for(unsigned int j = 0; j < m.m_ColumnCount; j++) 
                {
                    stream << m.at(i, j);

                    if(j < m.m_ColumnCount-1) {
                        stream << " ";
                    }
                }

                stream << "]" << std::endl;
            }

            return stream;
        } 
};

  