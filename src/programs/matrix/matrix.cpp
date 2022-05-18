#include <programs/matrix/matrix.h>
#include <cmath>

uint Matrix::row_count() const {
    return m_RowCount;
}

uint Matrix::column_count() const {
    return m_ColumnCount;
}

void Matrix::set(uint i, uint j, double value) {
    if(i < 1) throw ProgramException("Row identifier must be greater than 0.");
    if(j < 1) throw ProgramException("Column identifier must be greater than 0.");
    
    m_Matrix[i-1][j-1] = value;
    m_Empty = false;
    m_CanEmplace = false;
}

void Matrix::emplace(double value) {
    if(!m_CanEmplace) throw ProgramException("emplace can only be called if the Matrix is empty.");
    
    uint i = m_NextEmptyPos->get_i();
    uint j = m_NextEmptyPos->get_j();

    m_Matrix[i-1][j-1] = value;
    
    if(j < m_ColumnCount) // there are columns available 
    {
        j++;
    }
    else if(j == m_ColumnCount) // must be reset and add new row
    {
        j = 1;
        if(i < m_RowCount) // increment row if there are available
        {
            i++;
        }
        else // otherwise, mark as finished
        {
            m_CanEmplace = false;
            m_Empty = false;
            return;
        }
    }

    // Set next available position
    m_NextEmptyPos->set(i, j);
}

double Matrix::at(uint i, uint j) const {
    if(i < 1) throw ProgramException("Row identifier must be greater than 0.");
    if(j < 1) throw ProgramException("Column identifier must be greater than 0.");

    return m_Matrix[i-1][j-1];
}

bool Matrix::is_empty() const {
    return m_Empty;
}

bool Matrix::is_identity() const {
    if(m_Empty) {
        return false;
    }

    for(uint i = 0; i < m_RowCount; i++) {
        for(uint j = 0; j < m_ColumnCount; j++) {
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

Matrix Matrix::identity(uint rowCount, uint columnCount) {
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

Matrix Matrix::zero(uint rowCount, uint columnCount) {
    Matrix m(rowCount, columnCount);
    m.m_Empty = false;

    for(uint i = 0; i < rowCount; i++) 
    {
        for(uint j = 0; j < columnCount; j++) 
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
    for(uint i = 0; i < m_RowCount; i++) 
    {
        for(uint j = 0; j < m_ColumnCount; j++) 
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
    for(uint i = 0; i < m_RowCount; i++) {
        for(uint j = 0; j < m_ColumnCount; j++) {
            result += m_Matrix[i][j];
        }
    }

    return result;
}

Matrix Matrix::minor_complementary(uint i, uint j) {
    if(i < 1) throw ProgramException("Row identifier must be greater than 0.");
    if(j < 1) throw ProgramException("Column identifier must be greater than 0.");

    Matrix minor(m_RowCount-1, m_ColumnCount-1);

    for(uint row = 1; row <= m_RowCount; row++) 
    {
        if(row == i) {
            continue;
        }
        
        for(uint col = 1; col <= m_ColumnCount; col++) 
        {
            if(col == j) {
                continue;
            }

            // int newRow = row-1;
            // int newCol = col-1;

            // if(newRow < 1) newRow = 1;
            // if(newCol < 1) newCol = 1;

            minor.emplace(at(row, col));
        }
    }

    return minor;
}

double Matrix::determinant() {
    if(!is_square()) {
        throw ProgramException("Determinant is only available for square matrices.");
    }

    if(m_RowCount == 1)
    {
        return m_Matrix[0][0];
    }

    if(m_RowCount == 2) 
    {
        return (m_Matrix[0][0] * m_Matrix[1][1]) - (m_Matrix[0][1] * m_Matrix[1][0]);
    }

    // Row used to expand the matrix from
    const uint row = m_RowCount; // the last one
    double result = 0;
    
    for(uint col = 1; col <= m_ColumnCount; col++)
    {
        double cofactor = this->cofactor(row, col);
        // printf("Cofactor of %dx%d is: %f\n", row, col, cofactor);

        double valueAt = at(row, col);
        result = result + (valueAt * cofactor);
    }

    return result;
}

double Matrix::cofactor(uint i, uint j) {
    double factor = pow(-1, i+j);
    
    Matrix minor = this->minor_complementary(i, j);
    return factor * minor.determinant();
}

Matrix Matrix::add(const Matrix& m) const
{
    uint rowCount = 0;
    uint colCount = 0;

    if(m_RowCount > m.m_RowCount) rowCount = m_RowCount;
    else rowCount = m.m_RowCount;

    if(m_ColumnCount > m.m_ColumnCount) colCount = m_ColumnCount;
    else colCount = m.m_ColumnCount;

    Matrix result = Matrix::zero(rowCount, colCount);
    for(uint i = 1; i < m_RowCount; i++)
    {
        for(uint j = 1; j < m_ColumnCount; j++)
        {
            try 
            {
                double thisVal = at(i, j);
                double otherVal = m.at(i, j);
                result.set(i, j, thisVal+otherVal);
            }
            catch(const std::exception&)
            {
                result.set(i, j, 0);
            }
        }
    }

    return result;
}

Matrix Matrix::subtract(const Matrix& m) const
{
    uint rowCount = 0;
    uint colCount = 0;

    if(m_RowCount > m.m_RowCount) rowCount = m_RowCount;
    else rowCount = m.m_RowCount;

    if(m_ColumnCount > m.m_ColumnCount) colCount = m_ColumnCount;
    else colCount = m.m_ColumnCount;

    Matrix result = Matrix::zero(rowCount, colCount);
    for(uint i = 1; i < m_RowCount; i++)
    {
        for(uint j = 1; j < m_ColumnCount; j++)
        {
            try 
            {
                double thisVal = at(i, j);
                double otherVal = m.at(i, j);
                result.set(i, j, thisVal-otherVal);
            }
            catch(const std::exception&)
            {
                result.set(i, j, 0);
            }
        }
    }

    return result;
}

Matrix Matrix::multiply(double factor) const
{
    Matrix result(m_RowCount, m_ColumnCount);
    for(uint i = 1; i <= m_RowCount; i++)
    {
        for(uint j = 1; j <= m_ColumnCount; j++)
        {
            double value = at(i, j);
            result.set(i, j, value * factor);
        }
    }

    return result;
}

Matrix Matrix::multiply(const Matrix& m) const
{
    if(m_ColumnCount != m.m_RowCount) throw ProgramException("When multiplying two matrices, they must be conformable.");
    
    Matrix result(m_RowCount, m.m_ColumnCount);
    result.m_Empty = false;

    double temp = 0;
    for(uint i = 0; i < m_RowCount; i++)
    {
        for(uint j = 0; j < m.m_ColumnCount; j++)
        {
            temp = 0;
            for(uint k = 0; k < m_ColumnCount; k++)
                temp += m_Matrix[i][k] * m.m_Matrix[k][j];

            result.m_Matrix[i][j] = temp;
        }
    }

    return result;
}

Matrix Matrix::opposite()
{
    return multiply(-1);
}

bool Matrix::equals_to(const Matrix& m) const {
    if(m_RowCount != m.m_RowCount) return false;
    if(m_ColumnCount != m.m_ColumnCount) return false;
    if(m_Empty && m.m_Empty) return true;

    for(uint i = 1; i <= m_RowCount; i++) 
    {
        for(uint j = 1; j < m_ColumnCount; j++)
        {
            if(at(i, j) != m.at(i, j)) return false;
        }
    }

    return true;
}