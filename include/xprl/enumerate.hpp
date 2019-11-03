#ifndef __XPRL_ENUMERATE_IMPL__
#define __XPRL_ENUMERATE_IMPL__

#include <iterator>

namespace xprl {

    namespace {

        template<class Iter, class index_t = size_t>
        class indexed_iterator {
        public:
            using index_type = index_t;

        public:
            constexpr indexed_iterator(Iter const& rhs, index_type index=0)noexcept: iterator_(rhs), index_(index) {}

            constexpr bool operator!=(indexed_iterator const& rhs)const noexcept { return iterator_ != rhs.iterator_; }
            constexpr indexed_iterator& operator++()noexcept {
                return (++iterator_, ++index_, *this);
            }
            constexpr auto operator*()noexcept {
                return std::tuple<index_type&, decltype(*iterator_)>(index_, *iterator_);
            }
            constexpr auto operator*()const noexcept {
                return std::tuple<index_type&, decltype(*iterator_)>(index_, *iterator_);
            }

        private:
            Iter iterator_;
            index_type index_;
        };

    }

    template<class Range, class index_t = size_t>
    class enumerate {
    public:
        using index_type = index_t;

    public:
        constexpr explicit enumerate(Range& lhs)noexcept : range_(lhs) {}
        constexpr auto begin()noexcept { return indexed_iterator(std::begin(range_), static_cast<index_type>(0)); }
        constexpr auto end()noexcept { return indexed_iterator(std::end(range_), static_cast<index_type>(std::size(range_))); }
        constexpr auto begin()const noexcept { return indexed_iterator(std::begin(range_), static_cast<index_type>(0)); }
        constexpr auto end()const noexcept { return indexed_iterator(std::end(range_), static_cast<index_type>(std::size(range_))); }

    private:
        Range& range_;
    };


}



#endif