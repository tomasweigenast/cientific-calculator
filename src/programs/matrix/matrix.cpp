#include <programs/matrix/matrix.h>

unsigned int Matrix::row_count() const {
    return m_RowCount;
}

unsigned int Matrix::column_count() const {
    return m_ColumnCount;
}

void Matrix::set(unsigned int i, unsigned int j, double value) {
    m_Matrix[i][j] = value;
}

double Matrix::at(unsigned int i, unsigned int j) const {
    return m_Matrix[i][j];
}

Matrix Matrix::identity(unsigned int rowCount, unsigned int columnCount) {
    Matrix m(rowCount, columnCount);

    int j = 0;
    for(unsigned int i = 0; i < rowCount; i++) 
    {
        m.m_Matrix[i][j] = 1;
        j++;
    }

    return m;
}
