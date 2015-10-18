template<class To, class From> struct ForPartialSpecialization {
  static To reCast(const From& from ) { return (To) from;}
};
template<class To, class From> To reCast(const From& from) {
  return ForPartialSpecialization<To,From>::reCast(from);
}