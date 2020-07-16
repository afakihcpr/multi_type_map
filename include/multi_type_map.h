#ifndef MULTI_TYPE_MAP_H
#define MULTI_TYPE_MAP_H

#include <map>
#include <tuple>

namespace multi_type_map {

/**
* Manages a tuple of different valuetype maps using variadic templates
*/
template <typename KeyType, typename... Types>
class MultiTypeMap {
 private:
  using Maps = std::tuple<std::map<KeyType, Types>...>;
  Maps maps_;

  template <int N, typename T>
  using MapType =
      std::is_same<T, typename std::tuple_element<N, Maps>::type::mapped_type>;

  template <int N, class T, class Tuple, bool TypeMatch = false>
  struct MatchingMap {
    static size_t index() {
      return MatchingMap<N + 1, T, Tuple, MapType<N + 1, T>::value>::index();
    }

    static std::map<KeyType, T>& get(Tuple& tp) {
      return MatchingMap<N + 1, T, Tuple, MapType<N + 1, T>::value>::get(tp);
    }
  };

  template <int N, class T, class Tuple>
  struct MatchingMap<N, T, Tuple, true> {
    static size_t index() { return N; }
    static std::map<KeyType, T>& get(Tuple& tp) { return std::get<N>(tp); }
  };

 public:
  template <typename T>
  std::map<KeyType, T>& Map() {
    return MatchingMap<0, T, Maps, MapType<0, T>::value>::get(maps_);
  }

  template <typename T>
  T& operator[](const KeyType& k) {
    return Map<T>()[k];
  }

  template <typename T>
  auto& at(const KeyType& k) {
    return Map<T>().at(k);
  }

  template <typename T>
  const auto& at(const KeyType& k) const {
    return Map<T>().at(k);
  }

  template <typename T>
  auto find(const KeyType& k) {
    return Map<T>().find(k);
  }

  template <typename T>
  auto begin() {
    return Map<T>().begin();
  }

  template <typename T>
  const auto cbegin() const {
    return Map<T>().cbegin();
  }

  template <typename T>
  auto end() {
    return Map<T>().end();
  }

  template <typename T>
  const auto cend() const {
    return Map<T>().cend();
  }

  std::map<size_t, size_t> id_map_;
};
}  // namespace multi_type_map

#endif  //  MULTI_TYPE_MAP
