#pragma once

#include <matazure/config.hpp>
#include <matazure/point.hpp>

namespace matazure {

/**
 * \defgroup Tensor Memory Layout
 * @{
 */

template <int_t _Rank>
class column_major_layout {
   public:
    const static int_t rank = _Rank;

    MATAZURE_GENERAL column_major_layout(const pointi<rank>& shape) : shape_(shape) {
        stride_[0] = shape[0];
        for (int_t i = 1; i < rank; ++i) {
            stride_[i] = shape[i] * stride_[i - 1];
        }
    }

    MATAZURE_GENERAL column_major_layout(const column_major_layout& rhs)
        : column_major_layout(rhs.shape()) {}

    MATAZURE_GENERAL column_major_layout& operator=(const column_major_layout& rhs) {
        shape_ = rhs.shape();
        stride_ = rhs.stride();
        return *this;
    }

    MATAZURE_GENERAL int_t index2offset(const pointi<rank>& id) const {
        int_t offset = id[0];
        for (int_t i = 1; i < rank; ++i) {
            offset += id[i] * stride_[i - 1];
        }

        return offset;
    };

    MATAZURE_GENERAL pointi<rank> offset2index(int_t offset) const {
        pointi<rank> id{};
        for (int_t i = rank - 1; i > 0; --i) {
            id[i] = offset / stride_[i - 1];
            offset = offset % stride_[i - 1];
        }
        id[0] = offset;

        return id;
    }

    MATAZURE_GENERAL pointi<rank> shape() const { return shape_; }

    MATAZURE_GENERAL pointi<rank> stride() const { return stride_; }

    MATAZURE_GENERAL ~column_major_layout() {}

   private:
    pointi<rank> shape_;
    pointi<rank> stride_;
};

template <int_t _Rank>
class row_major_layout {
   public:
    const static int_t rank = _Rank;

    MATAZURE_GENERAL row_major_layout(const pointi<rank>& shape) : shape_(shape) {
        stride_[0] = shape[0];
        for (int_t i = 1; i < rank; ++i) {
            stride_[i] = shape[i] * stride_[i - 1];
        }
    }

    MATAZURE_GENERAL row_major_layout(const row_major_layout& rhs)
        : row_major_layout(rhs.shape()) {}

    MATAZURE_GENERAL row_major_layout& operator=(const row_major_layout& rhs) {
        shape_ = rhs.shape();
        stride_ = rhs.stride();
        return *this;
    }

    MATAZURE_GENERAL int_t index2offset(const pointi<rank>& id) const {
        typename pointi<rank>::value_type offset = id[rank - 1];
        for (int_t i = 1; i < rank; ++i) {
            offset += id[rank - 1 - i] * stride_[i - 1];
        }

        return offset;
    };

    MATAZURE_GENERAL pointi<rank> offset2index(int_t offset) const {
        pointi<rank> id{};
        for (int_t i = rank - 1; i > 0; --i) {
            id[rank - 1 - i] = offset / stride_[i - 1];
            offset = offset % stride_[i - 1];
        }
        id[rank - 1] = offset;

        return id;
    }

    MATAZURE_GENERAL pointi<rank> shape() const { return shape_; }

    MATAZURE_GENERAL pointi<rank> stride() const { return stride_; }

   private:
    pointi<rank> shape_;
    pointi<rank> stride_;
};

}  // namespace matazure
