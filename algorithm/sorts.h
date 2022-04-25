#include <functional>
#include <iostream>

namespace sort {

namespace detail {

template <typename Iter,
          typename T = typename std::iterator_traits<Iter>::value_type,
          typename Compare = std::less<T>>
static Iter partition(Iter begin, Iter end, Compare cmp = Compare{}) {
  const auto pv = *begin;
  Iter pivot = begin;
  for (auto it = std::next(begin, 1); it != end; ++it) {
    if (cmp(*it, pv)) {
      pivot = std::next(pivot, 1);
      std::iter_swap(it, pivot);
    }
  }
  std::iter_swap(begin, pivot);
  return pivot;
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

template <typename Iter,
          typename T = typename std::iterator_traits<Iter>::value_type,
          typename Compare = std::less<T>>
static void merge(Iter begin, Iter mid, Iter end, T* helper,
                  Compare cmp = Compare{}) {
  auto i = begin;
  auto j = mid;
  auto k = helper;

  while (i < mid && j < end) {
    if (cmp(*i, *j))
      *(k++) = *(i++);
    else
      *(k++) = *(j++);
  }

  while (i < mid) {
    *(k++) = *(i++);
  }

  while (j < end) {
    *(k++) = *(j++);
  }

  std::copy(helper, helper + std::distance(begin, end), begin);
}

template <typename Iter,
          typename T = typename std::iterator_traits<Iter>::value_type,
          typename Compare = std::less<T>>
static void merge(Iter begin, Iter end, T* helper, Compare cmp = Compare{}) {
  int len = std::distance(begin, end);
  if (len < 2) return;

  auto mid = begin;
  std::advance(mid, len / 2);

  auto helper_mid = helper + len / 2;
  // std::advance(helper_mid, len / 2);

  merge(begin, mid, helper, cmp);
  merge(mid, end, helper_mid, cmp);

  merge(begin, mid, end, helper, cmp);
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
static void bubble_sort(Iter begin, Iter end, Compare cmp = Compare{}) {
  if (std::distance(begin, end) <= 1) return;

  bool flag = true;
  for (Iter it = begin; flag && it != end; ++it) {
    for (Iter itt = begin; itt != end - std::distance(begin, it) - 1; ++itt) {
      flag = false;
      if (cmp(*std::next(itt, 1), *itt)) {
        std::iter_swap(itt, std::next(itt, 1));
        flag = true;
      }
    }
  }
}

template <typename Iter,
          typename T = typename std::iterator_traits<Iter>::value_type,
          typename Compare = std::less<T>>
static void shell_sort(Iter begin, Iter end, Compare cmp = Compare{}) {
  int len = std::distance(begin, end);
  if (len <= 1) return;
  int step = len;

  do {
    step = step / 3 + 1;
    for (Iter it = std::next(begin, step); std::distance(it, end) > 0;
         it += step) {
      for (Iter itt = it; std::distance(begin, itt) > 0; itt -= step) {
        if (cmp(*itt, *(std::next(itt, -step))))
          std::iter_swap(itt, std::next(itt, -step));
      }
    }
  } while (step > 1);
}

template <typename Iter,
          typename T = typename std::iterator_traits<Iter>::value_type,
          typename Compare = std::less<T>>
static void merge_sort(Iter begin, Iter end, Compare cmp = Compare{}) {
  int len = std::distance(begin, end);
  if (len <= 1) return;

  T* helper = new T[len];
  detail::merge(begin, end, helper, cmp);
  delete[] helper;
}

template <typename Iter,
          typename T = typename std::iterator_traits<Iter>::value_type,
          typename Compare = std::less<T>>
static void quick_sort(Iter begin, Iter end, Compare cmp = Compare{}) {
  if (std::distance(begin, end) <= 1) return;

  Iter pivot = detail::partition(begin, end, cmp);
  quick_sort(begin, pivot, cmp);
  quick_sort(pivot + 1, end, cmp);
}

template <typename Containter, typename T = typename Containter::value_type,
          typename Compare = std::less<T>>
static void heap_sort(Containter& containter, Compare cmp = Compare{}) {
  if (containter.size() <= 1) return;

  for (int i = containter.size() / 2 - 1; i >= 0; --i) {
    detail::make_heap(containter, containter.size(), i, cmp);
  }

  for (size_t i = containter.size() - 1; i > 0; --i) {
    std::swap(containter[i], containter[0]);
    detail::make_heap(containter, i, 0, cmp);
  }
}

template <size_t Size, typename Iter,
          typename Compare =
              std::less<typename std::iterator_traits<Iter>::value_type>>
static void bucket_sort(Iter begin, Iter end, Compare cmp = Compare{}) {
  auto [min, max] = std::minmax_element(begin, end);
  if (min == max) return;

  const size_t bucket_num = (*max - *min) / Size + 1;
  std::vector<std::vector<typename std::iterator_traits<Iter>::value_type>>
      buckets(bucket_num);
  for (auto& bucket : buckets) {
    bucket.reserve(2 * Size);
  }

  for (Iter it = begin; it != end; ++it) {
    size_t index = (*it - *min) / Size;
    buckets[index].emplace_back(*it);
  }

  Iter dest = begin;
  for (auto& bucket : buckets) {
    quick_sort(bucket.begin(), bucket.end(), cmp);
    std::copy(bucket.rbegin(), bucket.rend(), dest);
    std::advance(dest, bucket.size());
  }
}

template <typename Iter>
static void counting_sort(Iter begin, Iter end) {
  auto len = std::distance(begin, end);
  if (len <= 1) return;

  auto [min, max] = std::minmax_element(begin, end);
  if (*min < 0 || *min == *max) return;
  std::vector<size_t> counter(*max + 1, 0);

  for (Iter it = begin; it != end; ++it) {
    ++counter[*it];
  }

  /*
  for (int i = 1; i < counter.size(); ++i) {
    counter[i] += counter[i - 1];
  }
  */

  auto dest = begin;
  for (size_t i = 0; i < counter.size(); ++i) {
    if (counter[i] != 0) {
      int cnt = counter[i];
      while (cnt--) *(dest++) = i;
    }
  }
}

template <typename Iter>
void radix_sort(Iter begin, Iter end) {}

}  // namespace sort
