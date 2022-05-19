#include <iostream>
#include <iomanip>
#include <vector>
#include <util/id_generator.h>
#include <parser_exception/program_error.h>
#include <data/pos.h>
#include <mem/alloc_metric.h>

struct Matrix {
    private:
        uint m_RowCount;
        uint m_ColumnCount;
        double** m_Matrix;
        bool m_Empty;
        Pos* m_NextEmptyPos;
        bool m_CanEmplace;

        void initialize_() {
            if(m_RowCount < 1) throw ProgramException("Row count must be greater than 0.");
            if(m_ColumnCount < 1) throw ProgramException("Column count must be greater than 0.");

            m_Matrix = new double*[m_RowCount];
            for(uint i = 0; i < m_RowCount; i++) {
                m_Matrix[i] = new double[m_ColumnCount];
            }
        }

    public:
        Matrix() = delete;
        Matrix(const Matrix& other) 
            :   m_RowCount(other.m_RowCount), 
                m_ColumnCount(other.m_ColumnCount), 
                m_Empty(other.m_Empty),
                m_NextEmptyPos(other.m_NextEmptyPos),
                m_CanEmplace(other.m_CanEmplace)
        {
            initialize_();
            for(uint i = 0; i < other.m_RowCount; i++) {
                for(uint j = 0; j < other.m_ColumnCount; j++) {
                    double value = other.m_Matrix[i][j];
                    this->m_Matrix[i][j] = value;
                }
            }

            std::cout << "Matrix copied." << std::endl; 
        }
        Matrix(uint rowCount, uint columnCount) 
            :   m_RowCount(rowCount), 
                m_ColumnCount(columnCount), 
                m_Empty(true),
                m_NextEmptyPos(new Pos(1, 1)),
                m_CanEmplace(true)
        {
            initialize_();
        }
        Matrix(const std::vector<std::vector<double>>& rows, uint colCount) 
            :   m_RowCount(rows.size()), 
                m_ColumnCount(colCount), 
                m_Empty(false),
                m_NextEmptyPos(nullptr),
                m_CanEmplace(false)
        {
            uint i = 0;
            
            // Create initial matrix to hold "rows.size()" rows
            m_Matrix = new double*[m_RowCount];

            for(std::vector<double> cols : rows) 
            {
                // Create array to hold columns
                m_Matrix[i] = new double[cols.size()];

                uint j = 0;
                for(double value : cols) {
                    m_Matrix[i][j] = value;
                    j++;
                }

                i++;
            }
        }
        ~Matrix() {
            AllocationMetrics::instance().register_free(sizeof(m_Matrix));

            for(uint i = 0; i < m_RowCount; ++i) {
                delete[] m_Matrix[i];
            }

            delete[] m_Matrix;
            
            if(m_CanEmplace)
                delete m_NextEmptyPos;
        }

        uint row_count() const;
        uint column_count() const;
        bool is_empty() const;
        bool is_identity() const;
        bool is_square() const;
        void set(uint i, uint j, double value); // 1-index base
        void emplace(double value);
        void emplace(const std::initializer_list<double>& values);
        double at(uint i, uint j) const; // 1-index base
        double sum() const;
        double determinant();
        double cofactor(uint i, uint j);
        // std::vector<uint> rows() const;
        // std::vector<uint> columns() const;
        Matrix main_diagonal();
        Matrix secondary_diagonal();
        Matrix transpose();
        Matrix minor_complementary(uint i, uint j);
        Matrix add(const Matrix& m) const;
        Matrix subtract(const Matrix& m) const;
        Matrix multiply(double factor) const;
        Matrix multiply(const Matrix& m) const;
        Matrix opposite();

        bool equals_to(const Matrix& m) const;

        static Matrix identity(uint rowCount, uint columnCount);
        static Matrix zero(uint rowCount, uint columnCount);

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
        bool operator==(const Matrix& matrix) const 
        {
            return equals_to(matrix);
        }
        Matrix operator*(const Matrix& matrix) const 
        {
            return multiply(matrix);
        }
        Matrix operator*(double factor) const 
        {
            return multiply(factor);
        }
        Matrix operator+(const Matrix& matrix) const 
        {
            return add(matrix);
        }
        Matrix operator-(const Matrix& matrix) const 
        {
            return subtract(matrix);
        }
};