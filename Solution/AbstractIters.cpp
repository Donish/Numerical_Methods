#include "AbstractIters.h"

AbstractIters::AbstractIters(matrix &A): A(A), row_size(A.get_row_size()), column_size(A.get_column_size())
{}