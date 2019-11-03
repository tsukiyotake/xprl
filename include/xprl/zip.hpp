#ifndef __XPRL_ZIP_IMPL__
#define __XPRL_ZIP_IMPL__

#include <tuple>

namespace xprl {

    namespace {

        template<class...Iters>
        class packed_iterator {
        private:
            template<size_t ... index>
            constexpr bool neq_impl(packed_iterator const& rhs, std::index_sequence<index...> const&)const noexcept {
                return ((std::get<index>(iterators_) != std::get<index>(rhs.iterators_)) || ...);
            }

            template<size_t ... index>
            constexpr packed_iterator& increment_impl(std::index_sequence<index...> const&)noexcept {
                return (++std::get<index>(iterators_), ..., *this);
            }

            template<size_t ... index>
            constexpr auto reference_impl(std::index_sequence<index...> const&)noexcept {
                return std::tuple<decltype(*std::get<index>(iterators_))...>(*std::get<index>(iterators_)...);
            }

            template<size_t ... index>
            constexpr auto reference_impl(std::index_sequence<index...> const&)const noexcept {
                return std::tuple<std::add_const_t<(*iterators_[index])>...>(*std::get<index>(iterators_)...);

            }

        public:
            constexpr packed_iterator(Iters const& ... rhs) noexcept: iterators_{ rhs... } {}

            constexpr bool operator!=(packed_iterator const& rhs)const noexcept {
                return neq_impl(rhs, std::make_index_sequence<sizeof...(Iters)>());
            }

            constexpr packed_iterator& operator++()noexcept {
                return increment_impl(std::make_index_sequence<sizeof...(Iters)>());
            }

            constexpr auto operator*()noexcept {
                return reference_impl(std::make_index_sequence<sizeof...(Iters)>());
            }

            constexpr auto operator*()const noexcept {
                return reference_impl(std::make_index_sequence<sizeof...(Iters)>());
            }

        private:
            std::tuple<Iters...> iterators_;

        };
        
    }

    template<class ... Ranges>
    class zip {
    private:
        template<size_t ... index>
        auto begin(std::index_sequence<index...> const&)noexcept { return packed_iterator(std::begin(std::get<index>(packed_))...); }
        template<size_t ... index>
        auto end(std::index_sequence<index...> const&)noexcept { return packed_iterator(std::end(std::get<index>(packed_))...); }
        template<size_t ... index>
        auto begin(std::index_sequence<index...> const&)const noexcept { return packed_iterator(std::begin(std::get<index>(packed_))...); }
        template<size_t ... index>
        auto end(std::index_sequence<index...> const&)const noexcept { return packed_iterator(std::end(std::get<index>(packed_))...); }

    public:
        constexpr zip(Ranges &... lhs)noexcept : packed_{ lhs... } {}
        auto begin()noexcept { return begin(std::make_index_sequence<sizeof...(Ranges)>()); }
        auto end()noexcept { return end(std::make_index_sequence<sizeof...(Ranges)>()); }
        auto begin()const noexcept { return begin(std::make_index_sequence<sizeof...(Ranges)>()); }
        auto end()const noexcept { return end(std::make_index_sequence<sizeof...(Ranges)>()); }

    private:
        std::tuple<Ranges&...> packed_;
    };

}

#endif