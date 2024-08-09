#include <cassert>
#include <type_traits>
#include <memory>
#pragma once
template<typename T>
class Matrix
{
    private:
        std::unique_ptr<T[]> matrix_;
        uint8_t cols_;
        uint8_t rows_;
    public:
        Matrix() = delete;
        ~Matrix() = default;

        Matrix(
            uint8_t const& cols,
            uint8_t const& rows
        ) : cols_(cols),
            rows_(rows),
            matrix_(std::make_unique<T[]>(cols* rows))
        {
            for(uint16_t arr = 0; arr < cols*rows; arr++)
            {
                matrix_[arr] = 1;
            }
        }

        T* GetMatrix(
            void
        )
        {
            return matrix_.get();
        }

        uint8_t GetCols(
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
};