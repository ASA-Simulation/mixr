
#include "mixr/base/Matrix.hpp"
#include "mixr/base/Vectors.hpp"
#include "mixr/base/util/str_utils.hpp"
#include "mixr/base/util/math_utils.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>

namespace mixr {
namespace base {

IMPLEMENT_SUBCLASS(Matrix, "Matrix")
EMPTY_SLOTTABLE(Matrix)

Matrix::Matrix()
{
   STANDARD_CONSTRUCTOR()
}

Matrix::Matrix(const unsigned int r, const unsigned int c)
{
   STANDARD_CONSTRUCTOR()
   setMatrix(r,c);
}

Matrix::Matrix(const unsigned int r, const unsigned int c, const double* const data, const unsigned int dataSize)
{
   STANDARD_CONSTRUCTOR()
   setMatrix(r,c,data,dataSize);
}

Matrix::Matrix(const Matrixd& m)
{
   STANDARD_CONSTRUCTOR()
   *this = m;
}

Matrix::Matrix(const Matrixf& m)
{
   STANDARD_CONSTRUCTOR()
   *this = m;
}

void Matrix::copyData(const Matrix& org, const bool)
{
   BaseClass::copyData(org);

   emptyMatrix();

   rows = org.rows;
   cols = org.cols;
   const unsigned int arraySize{rows*cols};
   mda = new double[arraySize];

   for (unsigned int idx = 0; idx < arraySize; idx++) {
      mda[idx] = org.mda[idx];
   }
}

void Matrix::deleteData()
{
   emptyMatrix();
}

//------------------------------------------------------------------------------
// Assigned from an OSG matrix (double and float)
//------------------------------------------------------------------------------
Matrix& Matrix::operator=(const Matrixd& m)
{
   setMatrix(4,4,m.ptr(), 16);
   return *this;
}

Matrix& Matrix::operator=(const Matrixf& m)
{
   setMatrix(4,4,m.ptr(), 16);
   return *this;
}

//------------------------------------------------------------------------------
// Get functions
//------------------------------------------------------------------------------

unsigned int Matrix::getDecPoint() const
{
   return decPoint;
}

unsigned int Matrix::getFldWidth() const
{
   return fldWidth;
}

double Matrix::getMaxMag() const
{
   double val{mda[0]};
   double max{std::fabs(val)};
   for (unsigned int i = 0; i < rows; i++) {
      unsigned int idx{cols*i};
      for (unsigned int j = 0; j < cols; j++) {
         const double x{mda[idx]};
         const double y{std::fabs(x)};
         if (max < y) {
            max = y;
            val = x;
         }
         idx++;
      }
   }
   return val;
}

double Matrix::getMinMag() const
{
   double val{mda[0]};
   double min{std::fabs(val)};
   for (unsigned int i=0; i<rows; i++) {
      unsigned int idx = cols*i;
      for (unsigned int j=0; j<cols; j++) {
         const double x{std::fabs(mda[idx])};
         if (min > x) {
            val = mda[idx];
            min = x;
         }
         idx++;
      }
   }
   return val;
}

// Returns a pre-ref'd pointer to the transpose of this matrix
Matrix* Matrix::getTranspose() const
{
   const auto m = new Matrix(*this);
   m->transpose();
   return m;
}

// Returns a pre-ref'd pointer to the inverse of this matrix, or zero
// if the matrix can not be inverted
Matrix* Matrix::getInvGJ() const
{
   Matrix* m{};
   if (isSquare()) {
      m = new Matrix(*this);
      m->invert();
   }
   return m;
}

// Returns a pre-ref'd pointer to the inverse of this matrix, or zero
// if the matrix can not be inverted
Matrix* Matrix::getInvLU() const
{
   if (!isGoodMatrix() || !isSquare()) return nullptr;

   const unsigned int N{rows};
   const auto pL = new Matrix(N,N);
   const auto pU = new Matrix(N,N);
   getLU(pL, pU);

   const auto pB = new Matrix(N,N);
   pB->makeIdent();

   const auto pY = new Matrix(N,N);
   const auto pX = new Matrix(N,N);

   //-------------------------------------------------------
   // find Y from LY = I using forward substitution
   //-------------------------------------------------------
   for (unsigned int i = 0; i < N; i++) {
      for (unsigned int j = 0; j < N; j++) {
         (*pY)(i,j) = (*pB)(i,j);
         for (unsigned int k = 0; k < i; k++) {
            (*pY)(i,j) -= (*pL)(i,k) * (*pY)(k,j);
         }
      }
   }

   //-------------------------------------------------------
   // find X from UX = Y using back substitution
   //-------------------------------------------------------
   for (int i = (N-1); i >= 0; i--)
   {
      for (unsigned int j = 0; j < N; j++) {
         (*pX)(i,j) = (*pY)(i,j);
         for (int k = (N-1); k > i; k--) {
            (*pX)(i,j) -= (*pU)(i,k) * (*pX)(k,j);
         }
         (*pX)(i,j) /= (*pU)(i,i);
      }
   }

   pL->unref();
   pU->unref();
   pB->unref();
   pY->unref();

   return pX;
}

// matrix must be square and non-singular
double Matrix::getDeterm() const
{
   // check 'this' matrix for compatibility
   if (!isGoodMatrix() || !isSquare()) return 0.0;

   // get the L and U matrices
   const unsigned int N {rows};
   const auto pL = new Matrix(N,N);
   const auto pU = new Matrix(N,N);

   getLU(pL, pU);

   // find determinate by calculating product of U's diagonal elements
   double determ {1.0};
   for (unsigned int i = 0; i < N; i++) {
      determ *= (*pU)(i,i);
   }

   // unref pointers
   pL->unref();
   pU->unref();

   return determ;
}


//------------------------------------------------------------------------------
// Set functions
//------------------------------------------------------------------------------

// empty/clear the matrix
void Matrix::emptyMatrix()
{
   if (mda != nullptr) delete[] mda;
   mda = nullptr;
   rows = 0;
   cols = 0;
}

// Matrix with 'r' rows and 'c' columns and filled with zeros and ones on the diagonal
void Matrix::setMatrix(const unsigned int r, const unsigned int c)
{
   emptyMatrix();

   rows = r;
   cols = c;
   unsigned int arraySize {rows*cols};
   mda = new double[arraySize];

   for (unsigned int i = 0; i < arraySize; i++) {
      mda[i] = 0.0;
   }
}

// Matrix with 'r' rows and 'c' columns and filled with 'dataSize' values from the 'data' array.
void Matrix::setMatrix(const unsigned int r, const unsigned int c, const double* const data, const unsigned int dataSize)
{
   emptyMatrix();

   rows = r;
   cols = c;
   const unsigned int mdaSize{rows*cols};
   mda = new double[mdaSize];

   unsigned int idx{};
   while (idx < mdaSize && idx < dataSize) {
      mda[idx] = data[idx];
      idx++;
   }
   while (idx < mdaSize) {
      mda[idx++] = 0;
   }
}

// Matrix with 'r' rows and 'c' columns and filled with 'dataSize' values from the 'data' array.
void Matrix::setMatrix(const unsigned int r, const unsigned int c, const float* const data, const unsigned int dataSize)
{
   emptyMatrix();

   rows = r;
   cols = c;
   const unsigned int mdaSize{rows*cols};
   mda = new double[mdaSize];

   unsigned int idx{};
   while (idx < mdaSize && idx < dataSize) {
      mda[idx] = data[idx];
      idx++;
   }
   while (idx < mdaSize) {
      mda[idx++] = 0;
   }
}

bool Matrix::setElem(const unsigned int i, const unsigned int j, const double x)
{
   bool ok{isGoodIndex(i,j)};
   if (ok) {
      const unsigned int idx{i*cols + j};
      mda[idx] = x;
   }
   return ok;
}

bool Matrix::setDecPoint(const unsigned int DP)
{
   decPoint = DP;
   return true;
}

bool Matrix::setFldWidth(const unsigned int FW)
{
   fldWidth = FW;
   return true;
}

//------------------------------------------------------------------------------
// operator[]
//------------------------------------------------------------------------------
double* Matrix::operator[](unsigned int x)
{
   double* p{};
   if (x < rows) {
      const unsigned int idx{cols * x};
      p = &mda[idx];
   }
   return p;
}

const double* Matrix::operator[](unsigned int x) const
{
   const double* p{};
   if (x < rows) {
      const unsigned int idx{cols * x};
      p = &mda[idx];
   }
   return p;
}

//------------------------------------------------------------------------------
// Adds 'm' matrix to 'this' matrix and returns true;
// if 'm' is not compatible then 'this' matrix is unchanged and false is returned.
//------------------------------------------------------------------------------
bool Matrix::add(const Matrix& m)
{
   bool ok{};
   if (m.rows == rows || m.cols == cols) {
      for (unsigned int i=0; i<rows; i++) {
         unsigned int idx{cols*i};
         for (unsigned int j=0; j < cols; j++) {
            mda[idx] += m.mda[idx];
            idx++;
         }
      }
      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
// Subtracts 'm' matrix from 'this' matrix and returns true;
// if 'm' is not compatible then 'this' matrix is unchanged and false is returned.
//------------------------------------------------------------------------------
bool Matrix::subtract(const Matrix& m)
{
   bool ok{};
   if (m.rows == rows || m.cols == cols) {
      for (unsigned int i=0; i < rows; i++) {
         unsigned int idx{cols*i};
         for (unsigned int j=0; j < cols; j++) {
            mda[idx] -= m.mda[idx];
            idx++;
         }
      }
      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
// Multiplies 'this' matrix by 'm' matrix and returns true;
// if 'm' is not compatible then 'this' matrix is unchanged and false is returned.
//------------------------------------------------------------------------------
bool Matrix::multiply(const Matrix& m2)
{
   bool ok{};
   if (cols == m2.rows) {
      Matrix m1(*this);

      delete[] mda;
      rows = m1.rows;
      cols = m2.cols;
      mda = new double[rows * cols];

      for (unsigned int i=0; i < rows; i++) {
         for (unsigned int j=0; j < cols; j++) {
            unsigned int idx{cols*i + j};
            mda[idx] = 0.0;
            for (unsigned int k=0; k < m1.cols; k++) {
               unsigned int idx1{m1.cols*i + k};
               unsigned int idx2{m2.cols*k + j};
               mda[idx] += (m1.mda[idx1] * m2.mda[idx2]);
            }
         }
      }
      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
// Multiplies 'this' matrix by scalar 's' and returns true
//------------------------------------------------------------------------------
bool Matrix::multiply(const double s)
{
   for (unsigned int i=0; i<rows; i++) {
      unsigned int idx{cols*i};
      for (unsigned int j=0; j<cols; j++) {
         mda[idx++] *= s;
      }
   }
   return true;
}

//------------------------------------------------------------------------------
// Transpose
//------------------------------------------------------------------------------
bool Matrix::transpose()
{
   bool ok{mda != nullptr && rows > 0 && cols > 0};
   if (ok) {
      const auto temp = new double[rows*cols];

      for (unsigned int i=0; i<rows; i++) {
         for (unsigned int j=0; j<cols; j++) {
            unsigned int idx1{cols*i + j};
            unsigned int idx2{rows*j + i};
            temp[idx2] = mda[idx1];
         }
      }

      delete[] mda;
      mda = temp;

      if (rows != cols) {
         unsigned int xxxx{rows};
         rows = cols;
         cols = xxxx;
      }
   }
   return ok;
}

//------------------------------------------------------------------------------
// Invert
//------------------------------------------------------------------------------
bool Matrix::invert()
{
   bool ok{mda != nullptr && rows > 0 && cols > 0 && isSquare()};

   if (ok) {
      Matrix m(rows, cols);
      m.makeIdent();
      unsigned int origCols{cols};  // 'cols' is changed after augment()
      augment(m);

      for (unsigned int k = 0; k < origCols; k++) {
         pivotRow(k, k);
         mulRow(k, 1.0/getElem(k,k));
         for (unsigned int i=0; i<rows; i++) {
            if (i != k) {
               addRow(i, k, -getElem(i,k));
            }
         }
      }

      remCols(0, origCols-1);
   }
   return ok;
}

//------------------------------------------------------------------------------
// pivotRow
//------------------------------------------------------------------------------
bool Matrix::pivotRow(const unsigned int r, const unsigned int c)
{
   const bool l1{(r < rows-1)};
   const bool l2{(c < cols)};

   bool ok{};
   if (l1 && l2) {
      unsigned int refrow{r};
      double max{std::fabs(getElem(r,c))};

      for (unsigned int i=r+1; i<rows; i++) {
         const double val{std::fabs(getElem(i,c))};
         if (val > max) {
            refrow = i;
            max = val;
         }
      }

      if (r != refrow) {
         swapRow(r, refrow);
      }

      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
// pivotCol
//------------------------------------------------------------------------------
bool Matrix::pivotCol(const unsigned int r, const unsigned int c)
{
   // error check
   const bool l1{(r < rows)};
   const bool l2{(c < cols-1)};

   bool ok{};
   if (l1 && l2) {
      unsigned int refcol{c};
      double max{std::fabs(getElem(r,c))};

      for (unsigned int j=c+1; j<=cols; j++) {
         const double val{std::fabs(getElem(r,j))};
         if (val > max) {
            refcol = j;
            max = val;
         }
      }

      if (c != refcol) {
         //swapCol(c, refcol);

         const unsigned int c1{c};
         const unsigned int c2{refcol};
         for (unsigned int i=0; i<rows; i++) {
            const unsigned int idx1{i*cols + c1};
            const unsigned int idx2{i*cols + c2};
            const double xxxx{mda[idx1]};
            mda[idx1]  = mda[idx2];
            mda[idx2]  = xxxx;
         }
      }

      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
// augment
//------------------------------------------------------------------------------
bool Matrix::augment(const Matrix& m)
{
   bool ok{};
   if (rows == m.rows) {
      const auto arr = new double[rows*(cols + m.cols)];
      unsigned int idx{};
      for (unsigned int i=0; i<rows; i++) {
         unsigned int idx1{i*cols};
         for (unsigned int j=0; j<cols; j++) {
            arr[idx++] = mda[idx1++];
         }

         unsigned int idx2{i*m.cols};
         for (unsigned int k=0; k<m.cols; k++) {
            arr[idx++] = m.mda[idx2++];
         }
      }
      delete[] mda;
      mda = arr;
      cols += m.cols;

      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
// swapRow
//------------------------------------------------------------------------------
bool Matrix::swapRow(const unsigned int r1, const unsigned int r2)
{
   // error check
   const bool l1{(r1 < rows)};
   const bool l2{(r2 < rows)};

   bool ok{};
   if (l1 && l2) {
      if (r1 != r2) {
         unsigned int idx1{r1*cols};
         unsigned int idx2{r2*cols};
         for (unsigned int j=0; j<cols; j++) {
            const double xxxx{mda[idx1]};
            mda[idx1]  = mda[idx2];
            mda[idx2]  = xxxx;
            idx1++;
            idx2++;
         }
      }

      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
// swapCol
//------------------------------------------------------------------------------
bool Matrix::swapCol(const unsigned int c1, const unsigned int c2)
{
   // error check
   const bool l1{(c1 < cols)};
   const bool l2{(c2 < cols)};

   bool ok{};
   if (l1 && l2) {
      if (c1 != c2) {
         for (unsigned int i=0; i<rows; i++) {
            const unsigned int idx1{i*cols + c1};
            const unsigned int idx2{i*cols + c2};
            const double xxxx{mda[idx1]};
            mda[idx1]  = mda[idx2];
            mda[idx2]  = xxxx;
         }
      }
      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
// addRow
//------------------------------------------------------------------------------
bool Matrix::addRow(const unsigned int r1, const unsigned int r2, const double k)
{
   // error check
   const bool l1{(r1 < rows)};
   const bool l2{(r2 < rows)};
   const bool l3{(r1 != r2)};

   bool ok{};
   if (l1 && l2 && l3) {
      unsigned int idx1{r1*cols};
      unsigned int idx2{r2*cols};
      for (unsigned int j=0; j<cols; j++) {
         mda[idx1++] += k*mda[idx2++];
      }
      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
// addCol
//------------------------------------------------------------------------------
bool Matrix::addCol(const unsigned int c1, const unsigned int c2, const double k)
{
   // error check
   const bool l1{(c1 < cols)};
   const bool l2{(c2 < cols)};
   const bool l3{(c1 != c2)};

   bool ok{};
   if (l1 && l2 && l3) {
      for (unsigned int i=0; i<rows; i++) {
         const unsigned int idx1{cols*i + c1};
         const unsigned int idx2{cols*i + c2};
         mda[idx1] += k*mda[idx2];
      }
      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
// mulRow
//------------------------------------------------------------------------------
bool Matrix::mulRow(const unsigned int r, const double k)
{
   // error check
   const bool l1{(r < rows)};

   bool ok{};
   if (l1) {
      for (unsigned int j=0; j<cols; j++) {
         const unsigned int idx{cols*r + j};
         mda[idx] *= k;
      }
      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
// mulCol
//------------------------------------------------------------------------------
bool Matrix::mulCol(const unsigned int c, const double k)
{
   // error check
   const bool l1{(c < cols)};

   bool ok{};
   if (l1) {
      for (unsigned int i=0; i<rows; i++) {
         const unsigned int idx{cols*i + c};
         mda[idx] *= k;
      }
      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
// remRow
//------------------------------------------------------------------------------
bool Matrix::remRow(const unsigned int r)
{
   // error check
   const bool l1{(r < rows)};
   const bool l2{(0 < rows)};  // must have at least one row

   bool ok{};
   if (l1 && l2) {
      const auto arr = new double[(rows-1)*cols];
      unsigned int idx1{};
      for (unsigned int i=0; i<rows; i++) {
         for (unsigned int j=0; j<cols; j++) {
            if (i != r) {
               const unsigned int idx2{cols*i + j};
               arr[idx1] = mda[idx2];
               idx1++;
            }
         }
      }
      delete[] mda;
      mda = arr;
      rows--;

      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
// remRows
//------------------------------------------------------------------------------
bool Matrix::remRows(const unsigned int r1, const unsigned int r2)
{
   // error check
   const bool l1{(r1 < rows) && (r2 < rows)};
   const bool l2{(0 < rows)};

   bool ok{};
   if (l1 && l2) {
      const int rr{1 + std::abs(static_cast<int>(r2) - static_cast<int>(r1))};
      if (rr < static_cast<int>(rows)) {
         const auto arr = new double[(rows-rr)*cols];
         unsigned int idx1{};
         for (unsigned int i=0; i<rows; i++) {
            for (unsigned int j=0; j<cols; j++) {
               if ( ((i<r1) && (i<r2)) || ((r1<i) && (r2<i)) ) {
                  const unsigned int idx2{cols*i + j};
                  arr[idx1] = mda[idx2];
                  idx1++;
               }
            }
         }
         delete[] mda;
         mda = arr;
         rows -= rr;
      }
      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
// remCol
//------------------------------------------------------------------------------
bool Matrix::remCol(const unsigned int c)
{
   // error check
   const bool l1{(c < cols)};
   const bool l2{(0 < cols)};  // must have at least one column

   bool ok{};
   if (l1 && l2) {
      const auto arr = new double[rows*(cols-1)];
      unsigned int idx1{};
      for (unsigned int i=0; i<rows; i++) {
         for (unsigned int j=0; j<cols; j++) {
            if (j != c) {
               const unsigned int idx2{cols*i + j};
               arr[idx1] = mda[idx2];
               idx1++;
            }
         }
      }
      delete[] mda;
      mda = arr;
      cols--;
      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
// remCols
//------------------------------------------------------------------------------
bool Matrix::remCols(const unsigned int c1, const unsigned int c2)
{
   // error check
   const bool l1{(c1 < cols) && (c2 < cols)};
   const bool l2{(0 < cols)};

   bool ok{};
   if (l1 && l2) {
      const int cc{1 + std::abs(static_cast<int>(c2) - static_cast<int>(c1))};
      if (cc < static_cast<int>(cols)) {
         const auto arr = new double[rows*(cols-cc)];
         unsigned int idx1{};
         for (unsigned int i=0; i<rows; i++) {
            for (unsigned int j=0; j<cols; j++) {
               if ( ((j<c1) && (j<c2)) || ((c1<j) && (c2<j)) ) {
                  const unsigned int idx2{cols*i + j};
                  arr[idx1] = mda[idx2];
                  idx1++;
               }
            }
         }
         delete[] mda;
         mda = arr;
         cols -= cc;
      }
      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
// remRowCol
//------------------------------------------------------------------------------
bool Matrix::remRowCol(const unsigned int r, const unsigned int c)
{
   // error check
   const bool l1{(r < rows)};
   const bool l2{(c < cols)};
   const bool l3{(0 < rows) && (0 < cols)};  // (special cases - e.g. r=1,c=1 ??)

   bool ok{};
   if (l1 && l2 && l3) {
      const auto temp = new double[(rows-1)*(cols-1)];
      unsigned int idx1{};
      for (unsigned int i=0; i<rows; i++) {
         for (unsigned int j=0; j<cols; j++) {
            const bool b1{(i != r)};
            const bool b2{(j != c)};
            if (b1 && b2) {
               const unsigned int idx2{cols*i + j};
               temp[idx1++] = mda[idx2];
            }
         }
      }
      delete[] mda;
      mda = temp;
      rows--;
      cols--;
      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
// showMatrix
//------------------------------------------------------------------------------
void Matrix::showMatrix(const unsigned int DP, const unsigned int FW) const
{
   if (!isGoodMatrix()) {
      std::cout << "There is a problem displaying this matrix." << std::endl;
   } else {
      unsigned int decpnt = getDecPoint();
      if (DP != decpnt) {
         decpnt = DP;
      }

      unsigned int fldwth{};
      unsigned int gfw{getFldWidth()};
      unsigned int margin{3};
      unsigned int sum{decpnt};
      sum += (decpnt == 0 ? -1 : 0);
      sum += getDigits(getMaxMag());
      sum += margin;
      if (sum <= gfw) {
         fldwth = gfw;
      } else if (sum <= FW) {
         fldwth = FW;
      } else {
         fldwth = sum;
      }

      std::ios_base::fmtflags oldFmtFlgs =  std::cout.flags();
      std::streamsize oldprec = std::cout.precision();

      std::cout << std::setiosflags(std::ios::fixed)
         << std::setprecision(decpnt);

      for (unsigned int i=0; i<rows; i++) {
         for (unsigned int j=0; j<cols; j++) {
            const unsigned int idx{cols*i + j};
            std::cout << std::setw(fldwth) << mda[idx];
         }
         std::cout << std::endl;
      }
      std::cout.setf(oldFmtFlgs);
      std::cout << std::setprecision(oldprec);
   }
}

//------------------------------------------------------------------------------
// operator<<
//------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& sout, const Matrix& m)
{
   if (!m.isGoodMatrix()) {
      sout << "There is a problem displaying this matrix." << std::endl;
   } else {
      const unsigned int DECPNT{m.getDecPoint()};
      const unsigned int DPZERO = (DECPNT == 0 ? -1 : 0);
      const unsigned int DIGITS{getDigits(m.getMaxMag())};
      const unsigned int MARGIN{3};
      const unsigned int FLDWTH{DECPNT + DPZERO + DIGITS + MARGIN};

      std::ios_base::fmtflags oldFmtFlgs =  sout.flags();
      std::streamsize oldprec = sout.precision();

      sout << std::setprecision(DECPNT)
         << std::setiosflags(std::ios::fixed);

      for (unsigned int i=0; i<m.rows; i++) {
         for (unsigned int j=0; j<m.cols; j++) {
            sout << std::setw(FLDWTH) << m[i][j];
         }
         sout << std::endl;
      }

      sout.setf(oldFmtFlgs);
      sout << std::setprecision(oldprec);

   }
   return sout;
}


//------------------------------------------------------------------------------
// makeZero
//------------------------------------------------------------------------------
bool Matrix::makeZero()
{
   if (!isGoodMatrix()) {
      return false;
   }

   const unsigned int SIZE{rows * cols};
   for (unsigned int i = 0; i < SIZE; i++) {
      mda[i] = 0.0;
   }
   return true;
}

//------------------------------------------------------------------------------
// makeIdent
//------------------------------------------------------------------------------
bool Matrix::makeIdent()
{
   if (!isGoodMatrix() || !isSquare()) {
      return false;
   }

   for (unsigned int i = 0; i < rows; i++) {
      unsigned int idx{cols*i};
      for (unsigned int j=0; j< cols; j++) {
         if (i == j)
            mda[idx] = 1.0;
         else
            mda[idx] = 0.0;
         idx++;
      }
   }
   return true;
}

//------------------------------------------------------------------------------
// makeIdent (overloaded version)
//------------------------------------------------------------------------------
bool Matrix::makeIdent(const unsigned int k)
{
   if (k < 1) return false;

   setMatrix(k,k);
   makeIdent();
   return true;
}

//------------------------------------------------------------------------------
// isSymmetric
//------------------------------------------------------------------------------
bool Matrix::isSymmetric() const
{
   if (!isGoodMatrix() || !isSquare()) {
      return false;
   }

   const unsigned int N{rows};
   for (unsigned int i = 0; i < N-1; i++) {
      for (unsigned int j = i+1; j < N; j++) {
         unsigned int idx1{N*i + j};
         unsigned int idx2{N*j + i};
         if (mda[idx1] != mda[idx2]) return false;
      }
   }
   return true;
}

//------------------------------------------------------------------------------
// Dominant Eigenvalue Power Method
//------------------------------------------------------------------------------
bool Matrix::getEigenPower(const double maxErr, const int maxIter,
   double* const pEigenVal, CVector* const pEigenVec)
{
   //-------------------------------------------------------
   // initial compatibility and error checks
   //-------------------------------------------------------
   if (!isGoodMatrix() || !isSquare()) return false;

   //-------------------------------------------------------
   // initialize variables
   //-------------------------------------------------------
   int Iter{};                            // iterator initialized to zero
   double Err{10.0*maxErr};               // make Err > maxErr on entry

   const auto pA = new Matrix(*this);     // A is a buffer matrix for 'this' matrix
   const unsigned int N{pA->getRows()};   // pA->getCols works too since A is square

   double alfa{};                         // current eigenvalue estimate
   const auto pZ = new CVector(N);        // current eigenvector estimate
   pZ->fillWith(1.0);                     // all 1's in initial estimate

   //-------------------------------------------------------
   // iterate solutions to desired accuracy or iteration limit
   //-------------------------------------------------------
   while ((Err > maxErr) && (Iter < maxIter))
   {
      {
         //----------------------------------------------------
         // get estimate of eigenvector
         //----------------------------------------------------
         CVector* pW{base::multiply(*pA, *pZ)};   // get new estimate (W) based on old estimate (Z)
         const double Wmag{pW->getMaxMag()};      // max mag value from elements of vector W
         if (Wmag == 0.0) {
            // mag value is zero; cleanup and leave
            pW->unref();
            pZ->unref();
            pA->unref();
            return false;
         }
         pW->multiply(1.0/Wmag);           // normalize eigenvector with max element of W

         //----------------------------------------------------
         // get estimate of eigenvalue
         //----------------------------------------------------
         alfa = Wmag;                   // save Wmag eigenvalue estimate

         //----------------------------------------------------
         // refine eigenvalue estimate by using Rayleigh quotient
         // (may or may not be worth the additional calculations)
         //----------------------------------------------------
#if 0
         {
            RVector* pZT = pZ->getTranspose();
            double num = base::dotProduct(*pZT, *pW);
            double den = base::dotProduct(*pZT, *pZ);
            alfa *= (num / den);  // save Rayleigh eigenvalue estimate
            pZT->unref();
         }
#endif

         //----------------------------------------------------
         // save eigenvector W estimate in vector Z to begin next loop
         //----------------------------------------------------
         *pZ = *pW;                        // save eigenvector estimate for next iteration
         pW->unref();
      }

      //----------------------------------------------------
      // calculate error of estimate: Err = ||A*Z - alfa*Z||
      //----------------------------------------------------
      {
         CVector* pE{base::multiply(*pA, *pZ)};
         CVector* pW1{base::multiply(*pZ, alfa)};  // pW1 used here as intermediate vector
         pE->subtract(*pW1);
         Err = pE->getNorm();              // magnitude of error vector
         pE->unref();
         pW1->unref();
      }

      //----------------------------------------------------
      // increment iterator for next loop
      //----------------------------------------------------
      Iter++;
   }

   //-------------------------------------------------------
   // copy eigenvalue and eigenvector results to output
   //-------------------------------------------------------
   *pEigenVal = alfa;
   *pEigenVec = *pZ;

   //-------------------------------------------------------
   // unref pointers
   //-------------------------------------------------------
   pZ->unref();
   pA->unref();

   return true;
}


//------------------------------------------------------------------------------
// Returns pre-ref'd pointers to the Cholesky (pL) of 'this' matrix and its
// transpose (pU). Function returns false if the matrix can not be Cholesky-ized
//------------------------------------------------------------------------------
bool Matrix::getCholesky(Matrix* const pL, Matrix* const pU) const
{
   //-------------------------------------------------------
   // initial compatibility and error checks
   //-------------------------------------------------------
   if (!isSymmetric()) return false;

   //-------------------------------------------------------
   // calculate the lower Cholesky matrix
   //-------------------------------------------------------
   const unsigned int N{rows};
   for (unsigned int j = 0; j < N; j++) {
      for (unsigned int i = j; i < N; i++) {
         (*pL)(i,j) = (*this)(i,j);
         for (unsigned int k=0; k<j; k++) {
            (*pL)(i,j) -= (*pL)(i,k) * (*pL)(j,k);
         }

         if (i == j) {
            double x{(*pL)(i,j)};
            if (x < 0.0) {
               std::cout << "Cholesky failed. Matrix is not positive definite." << std::endl;
               return false;
            }
            (*pL)(i,j) = std::sqrt(x);
         }
         else {
            double x{(*pL)(j,j)};
            double eps{1.0e-12};
            if (std::fabs(x) < eps) {
               // Note: excessive roundoff error for some reason - LDB
               std::cout << "Cholesky failed. Division by very small number." << std::endl;
               return false;
            }
            (*pL)(i,j) /= x;
         }
      }
   }

   //-------------------------------------------------------
   // upper Cholesky matrix is the transpose of lower matrix
   //-------------------------------------------------------
   *pU = *pL;
   pU->transpose();

   return true;
}

//------------------------------------------------------------------------------
// Returns pre-ref'd pointers to the lower LU (pL) and upper LU (pU) matrices of
// 'this' matrix. Function returns zero if the matrix can not be LU-ized
//------------------------------------------------------------------------------
bool Matrix::getLU(Matrix* const pL, Matrix* const pU) const
{
   //-------------------------------------------------------
   // initial compatibility and error checks
   //-------------------------------------------------------
   const bool b1{isGoodMatrix()};
   const bool b2{isSquare()};
   if (!b1 || !b2) {
      return false;
   }

   const unsigned int N{rows};
   pL->makeIdent();
   pU->makeZero();

   for (unsigned int i=0; i<N; i++) {
      (*pU)(i,i) = (*this)(i,i);
      for (unsigned int q=0; q<i; q++) {
         (*pU)(i,i) -= (*pL)(i,q) * (*pU)(q,i);
      }

      for (unsigned int j=i+1; j<N; j++) {
         (*pU)(i,j) = (*this)(i,j);
         (*pL)(j,i) = (*this)(j,i);

         for (unsigned int k=0; k<i; k++) {
            (*pU)(i,j) -= (*pL)(i,k) * (*pU)(k,j);
            (*pL)(j,i) -= (*pL)(j,k) * (*pU)(k,i);
         }

         (*pL)(j,i) /= (*pU)(i,i);
      }
   }

   return true;
}


//------------------------------------------------------------------------------
// getQR
// Returns pre-ref'd pointers to the lower QR (pQ) and upper QR (pR) matrices
// of 'this' matrix, or zero if the matrix can not be QR-ized
//------------------------------------------------------------------------------
bool Matrix::getQR(Matrix* const pQ, Matrix* const pR) const
{
   //-------------------------------------------------------
   // initial compatibility and error checks
   //-------------------------------------------------------
   const bool b1{isGoodMatrix()};
   const bool b2{isSquare()};
   if (!b1 || !b2) return false;

   //-------------------------------------------------------
   // Initialize intermediate R matrix to 'this' matrix
   //-------------------------------------------------------
   const auto pRI = new Matrix(*this);

   //-------------------------------------------------------
   // Initialize intermediate Q matrix to 'identity' matrix
   //-------------------------------------------------------
   const int N{static_cast<int>(getRows())};
   const auto pQI = new Matrix(N,N);
   pQI->makeIdent();

   //-------------------------------------------------------
   // X and V are intermediate vectors
   //-------------------------------------------------------
   const auto pX = new CVector(N);
   const auto pV = new CVector(N);

   //-------------------------------------------------------
   // Begin loop
   //-------------------------------------------------------
   for (int k = 0; k < (N-1); k++) {

      pX->fillWith(0.0);
      for (int i = k; i<N ; i++) {
         (*pX)[i] = (*pRI)(i,k);
      }

      double g{pX->getNorm()};
      (*pV) = (*pX);
      (*pV)[k] += g;
      double s{pV->getNorm()};

      if (s == 0.0) {
         pQI->unref();
         pRI->unref();
         pX->unref();
         pV->unref();
         return false;
      }

      CVector* pW{base::multiply((*pV), 1.0/s)};
      RVector* pWT{pW->getTranspose()};

      {
         //----------------------------------------------------
         // U' = (2*R'*W)'
         //----------------------------------------------------
         Matrix* pRIT{pRI->getTranspose()};
         CVector* pU0{base::multiply((*pRIT), (*pW))};
         CVector* pU{base::multiply((*pU0), 2.0)};
         RVector* pUT{pU->getTranspose()};
         pU0->unref();
         pU->unref();
         pRIT->unref();

         //----------------------------------------------------
         // R = R - W*U'
         //----------------------------------------------------
         Matrix* pM1{outerProduct(*pW, *pUT)};
         pRI->subtract(*pM1);
         pM1->unref();
         pUT->unref();
      }

      //----------------------------------------------------
      // Q = Q - 2*Q*W*W'
      //----------------------------------------------------
      {
         Matrix* pM2{outerProduct(*pW, *pWT)};
         Matrix* pM3{base::multiply(*pQI, *pM2)};
         Matrix* pM4{base::multiply(*pM3, 2.0)};
         pQI->subtract(*pM4);
         pM2->unref();
         pM3->unref();
         pM4->unref();
      }

      //-------------------------------------------------------
      // Unref pointers
      //-------------------------------------------------------
      pW->unref();
      pWT->unref();
   }

   //-------------------------------------------------------
   // Assign results to argument list variables for output
   //-------------------------------------------------------
   *pQ = *pQI;
   *pR = *pRI;

   //-------------------------------------------------------
   // Unref pointers
   //-------------------------------------------------------
   pQI->unref();
   pRI->unref();
   pX->unref();
   pV->unref();

   return true;
}


//------------------------------------------------------------------------------
// getTriDiagonal
//------------------------------------------------------------------------------
bool Matrix::getTriDiagonal(Matrix* const pA) const
{
   //-------------------------------------------------------
   // initial compatibility and error checks
   //-------------------------------------------------------
   //if (!isSymmetric()) return 0;

   const int N{static_cast<int>(getRows())};
   const auto pAI = new Matrix(*this);

   for (int k=0; k<N-2; k++) {
      double gama{(*pAI)(k+1,k)};
      double alfa{(gama * gama)};
      for (int j=k+2; j<N; j++) {
         double zeta{(*pAI)(j,k)};
         alfa += (zeta * zeta);
      }

      alfa = -sign(gama) * std::sqrt(alfa);
      double beta{std::sqrt(0.5 * alfa * (alfa - gama))};

      //----------------------------------------------------
      // construct column vector X
      //----------------------------------------------------
      const auto pX = new CVector(N);
      for (int p=0; p<k+1; p++) {
         (*pX)[p] = 0.0;
      }

      (*pX)[k+1] = (gama - alfa) / beta / 2.0;

      for (int q=k+2; q<N; q++) {
         (*pX)[q] = (*pAI)(q,k) / beta / 2.0;
      }

      //----------------------------------------------------
      // construct row vector Y = X'
      //----------------------------------------------------
      RVector* pY{pX->getTranspose()};

      //----------------------------------------------------
      // M = 2*X*Y = 2*X*X'
      //----------------------------------------------------
      Matrix* pM{outerProduct(*pX, *pY)};
      pM->multiply(2.0);

      //----------------------------------------------------
      // H = I - M = I - 2*X*X'
      //----------------------------------------------------
      const auto pH = new Matrix(N,N);
      pH->makeIdent();
      pH->subtract(*pM);

      //----------------------------------------------------
      // A = H*A*H
      //----------------------------------------------------
      Matrix* pAI0{base::multiply(*pH, *pAI)};
      Matrix* pAI1{base::multiply(*pAI0, *pH)};
      *pAI = *pAI1;

      //----------------------------------------------------
      // unref intermediate loop pointers
      //----------------------------------------------------
      pX->unref();
      pY->unref();
      pM->unref();
      pH->unref();
      pAI0->unref();
      pAI1->unref();
   }

   //-------------------------------------------------------
   // A = H(N-3)*...*H1*H0* A *H0*H1*...*H(N-3)
   //-------------------------------------------------------
   *pA = *pAI;

   //----------------------------------------------------
   // unref pointers
   //----------------------------------------------------
   pAI->unref();

   return true;
}

}
}
