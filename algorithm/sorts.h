#include <functional>
#include <iterator>

namespace sort {

namespace detail {

template <typename Iter,
          typename T = typename std::iterator_traits<Iter>::value_type,
          typename Compare = std::less<T>>
static Iter partition(Iter begin, Iter end, Compare cmp = Compare{}) {
  const auto pv = *begin;
  Iter piovt = begin;
  for (auto it = std::next(begin, 1); it != end; ++it) {
    if (cmp(*it, pv)) {
      piovt = std::next(piovt, 1);
      std::iter_swap(it, piovt);
    }
  }
  std::iter_swap(begin, piovt);
  return piovt;
}

template <typename Containter, typename T = typename Containter::value_type,
          typename Compare = std::less<T>>
static void make_heap(Containter& containter, size_t length, size_t index,
                      Compare cmp = Compare{}) {
  size_t largest = index;
  size_t left = index * 2 + 1;
  size_t right = index * 2 + 2;

  if (left < length && cmp(containter[largest], containter[left]))
    largest = left;
  if (right < length && cmp(containter[largest], containter[right]))
    largest = right;

  if (largest != index) {
    std::swap(containter[largest], containter[index]);
    make_heap(containter, length, largest);
  }
}

}  // namespace detail

template <typename Iter,
          typename T = typename std::iterator_traits<Iter>::value_type,
          typename Compare = std::less<T>>
static void insertion_sort(Iter begin, Iter end, Compare cmp = Compare{}) {
  if (std::distance(begin, end) <= 1) return;

  for (Iter it = begin + 1; it != end; ++it) {
    for (Iter itt = it; std::distance(begin, itt) > 0; --itt) {
      if (cmp(*itt, *(std::next(itt, -1))))
        std::iter_swap(itt, std::next(itt, -1));
    }
  }
}

template <typename Iter,
          typename T = typename std::iterator_traits<Iter>::value_type,
          typename Compare = std::less<T>>
static void selection_sort(Iter begin, Iter end, Compare cmp = Compare{}) {
  if (std::distance(begin, end) <= 1) return;

  for (Iter it = begin; it != std::next(end, -1); ++it) {
    auto memo = it;
    for (Iter itt = std::next(it, 1); itt != end; ++itt) {
      if (cmp(*itt, *memo)) memo = itt;
    }
    if (memo != it) std::iter_swap(it, memo);
  }
}

template <typename Iter,
          typename T = typename std::iterator_traits<Iter>::value_type,
          typename Compare = std::less<T>>
static void quick_sort(Iter begin, Iter end, Compare cmp = Compare{}) {
  if (std::distance(begin, end) <= 1) return;
  Iter piovt = detail::partition(begin, end, cmp);
  quick_sort(begin, piovt, cmp);
  quick_sort(piovt + 1, end, cmp);
}

template <typename Containter, typename T = typename Containter::value_type,
          typename Compare = std::less<T>>
static void heap_sort(Containter& containter, Compare cmp = Compare{}) {
  for (int i = containter.size() / 2 - 1; i >= 0; --i) {
    detail::make_heap(containter, containter.size(), i, cmp);
  }

  for (size_t i = containter.size() - 1; i > 0; --i) {
    std::swap(containter[i], containter[0]);
    detail::make_heap(containter, i, 0, cmp);
  }
}

}  // namespace sort