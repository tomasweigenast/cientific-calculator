#include <programs/matrix/matrix.h>

unsigned int Matrix::row_count() const {
    return m_RowCount;
}

unsigned int Matrix::column_count() const {
    return m_ColumnCount;
}

void Matrix::set(unsigned int i, unsigned int j, double value) {
    m_Matrix[i][j] = value;
    m_Empty = false;
}

double Matrix::at(unsigned int i, unsigned int j) const {
    return m_Matrix[i][j];
}

bool Matrix::is_empty() const {
    return m_Empty;
}

bool Matrix::is_identity() const {
    if(m_Empty) {
        return false;
    }

    for(int i = 0; i < m_RowCount; i++) {
        for(int j = 0; j < m_ColumnCount; j++) {
            if(m_Matrix[i][j] != 0) {
                return false;
            }
        }
    }

    return true;
}

bool Matrix::is_square() const {
    return m_ColumnCount == m_RowCount;
}

Matrix Matrix::identity(unsigned int rowCount, unsigned int columnCount) {
    if(rowCount != columnCount) {
        throw ProgramException("Identity matrix must be square.");
    }

    Matrix m(rowCount, columnCount);
    m.m_Empty = false;

    uint j = 0;
    for(uint i = 0; i < rowCount; i++) 
    {
        m.m_Matrix[i][j] = 1;
        j++;
    }

    return m;
}

Matrix Matrix::zero(unsigned int rowCount, unsigned int columnCount) {
    Matrix m(rowCount, columnCount);
    m.m_Empty = false;

    for(unsigned int i = 0; i < rowCount; i++) 
    {
        for(unsigned int j = 0; j < columnCount; j++) 
        {
            m.m_Matrix[i][j] = 0;
        }
    }

    return m;
}

Matrix Matrix::main_diagonal() {
    if(m_Empty) {
        return Matrix::zero(m_RowCount, m_ColumnCount);
    }

    Matrix m = Matrix::zero(m_RowCount, m_ColumnCount);
    
    uint j = 0;
    for(uint i = 0; i < m_RowCount; i++) 
    {
        double value = m_Matrix[i][j];
        m.set(i, j, value); 
        j++;
    }

    return m;
}

Matrix Matrix::secondary_diagonal() {
    if(m_Empty) {
        return Matrix::zero(m_RowCount, m_ColumnCount);
    }

    Matrix m = Matrix::zero(m_RowCount, m_ColumnCount);
    
    uint j = m_ColumnCount-1;
    for(uint i = 0; i < m_RowCount; i++) 
    {
        double value = m_Matrix[i][j];
        m.set(i, j, value); 
        j--;
    }

    return m;
}

Matrix Matrix::transpose() {
    if(m_Empty) {
        return Matrix::zero(m_RowCount, m_ColumnCount);
    }

    Matrix m = Matrix::zero(m_ColumnCount, m_RowCount);
    for(int i = 0; i < m_RowCount; i++) 
    {
        for(int j = 0; j < m_ColumnCount; j++) 
        {
            m.set(j, i, m_Matrix[i][j]);
        }
    }

    return m;
}

double Matrix::sum() const {
    if(m_Empty) {
        return 0;
    }

    double result = 0;
    for(int i = 0; i < m_RowCount; i++) {
        for(int j = 0; j < m_ColumnCount; j++) {
            result += m_Matrix[i][j];
        }
    }

    return result;
}