#include <memory>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cassert>
#include <type_traits>
#pragma once
template<typename T>
class Matrix
{
    private:
        std::unique_ptr<T[]> matrix_;
        uint16_t cols_;
        uint16_t rows_;
    public:
        Matrix() = default;
        ~Matrix() = default;
        Matrix(
            uint16_t const& cols,
            uint16_t const& rows
        ) : cols_   {cols},
            rows_   {rows}
        {
            matrix_ = std::make_unique<T[]>(cols_ * rows_);
        }
        void SetMatrix(
            uint16_t const& rows,
            uint16_t const& cols,
            T* imgData
        )
        {
            matrix_ = imgData;
            cols_ = cols;
            rows_ = rows;
        }
        void CreateRotMatrix(
            double const& angle
        )
        {
            assert(cols_ == 3 && rows_ == 3);
            assert(std::is_floating_point<T>());
            matrix_ = std::make_unique<T[]>(cols_ * rows_);
            matrix_[0] = 1;
            for(uint16_t idx = 1; idx < rows_ * cols_; idx++)
            {
                if(idx % cols_ == idx / cols_)
                {
                    matrix_[idx] = std::cos( ( angle * M_PI/180.0) );
                }
                else if(idx % cols_ + idx / cols_ == cols_)
                {
                    if(idx % cols_ > idx / cols_)
                    {
                        matrix_[idx] = -std::sin(( angle * M_PI/180.0 )); /// angle );
                    }
                    else
                    {
                        matrix_[idx] = std::sin(( angle * M_PI/180.0 )); /// angle );
                    }
                }
                else
                {
                    matrix_[idx] = 0;
                }
            }
        }
        void FillMatrix(
            T const& value
        )
        {
            for(uint16_t arr = 0; arr < cols_ * rows_; arr++)
            {
                matrix_[arr] = value;
            }
        }
        void SetMatrixValue(
            uint8_t const& col,
            uint8_t const& row,
            T const& value
        )
        {
            matrix_[row * cols_ + col] = value;
        }

        T* GetMatrix(
            void
        )
        {
            return matrix_.get();
        }

        uint16_t GetCols(
            void
        )
        {
            return cols_;
        }

        uint16_t GetMatrixSize(
            void
        )
        {
            return cols_ * rows_;
        }
        void operator=(
            Matrix<T> const& c1
        )
        {
            this->cols_ = c1.cols_;
            this->rows_ = c1.rows_;
            memcpy(matrix_, c1.matrix_, cols_ * rows_ * sizeof(T));
            // memcpy(rotMat_.get(), c1.rotMat_.get(), 3 * 3 * sizeof(float));
            // c1.rotMat_.swap(rotMat_);
        }
};


template<class T>
class Math
{
    public:
        Math() = delete;
        ~Math() = delete;
        
        static void MultiplyMatrix(
            T* const a,
            T* const b,
            T* result
        )
        {
            assert(a->GetCols() == b->GetMatrixSize() / b->GetCols());
            T* matA = a->GetMatrix();
            T* matB = b->GetMatrix();
            T sum{static_cast<T>(0)};
            *result = T(b->GetCols() , a->GetMatrixSize() / a->GetCols());
            for(uint16_t rows = 0; rows < result->GetMatrixSize(); rows++)
            {
                sum = static_cast<T>(0);
                for(uint16_t indxMultipy = 0; indxMultipy < a->GetCols(); indxMultipy++)
                {
                    sum += a->GetMatrix()[indxMultipy + rows / result->GetCols() * a->GetCols()] * 
                           b->GetMatrix()[indxMultipy * b->GetCols() + rows % result->GetCols()];
                }
                result->GetMatrix()[rows] = sum;
            }
        }
};