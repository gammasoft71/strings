#include <xtd/strings>
#include <xtd/tunit>

using namespace std;
using namespace std::string_literals;
using namespace xtd;
using namespace xtd::tunit;

namespace unit_tests {
  template <typename Value>
  class test_fixed_point_format;
  
  test_class_attribute<test_fixed_point_format<float>> test_fixed_point_format_class_float_attr {"test_fixed_point_format<float>"};
  test_class_attribute<test_fixed_point_format<double>> test_fixed_point_format_class_double_attr {"test_fixed_point_format<double>"};
  test_class_attribute<test_fixed_point_format<long double>> test_fixed_point_format_class_long_double_attr {"test_fixed_point_format<long double>"};

  template<typename Value>
  class test_fixed_point_format : public test_class {
  private:
    template<typename V>
    static V to_value(V value) {return value;}
    
  public:
    void test_method_(format_with_default_argument) {
      assert::are_equal("42", strings::format("{0}", to_value<Value>(42.0)));
    }
    
    void test_method_(format_with_decimals_with_default_argument) {
      assert::are_equal("42.24", strings::format("{0}", to_value<Value>(42.24)));
    }

    void test_method_(format_without_format_argument_separator) {
      assert::throws<std::invalid_argument>([]{strings::format("{0F}", to_value<Value>(42.24));});
    }
    
    void test_method_(format_with_left_alignment) {
      assert::are_equal("  42.24", strings::format("{0,7}", to_value<Value>(42.24)));
    }
    
    void test_method_(format_with_left_alignment_with_plus) {
      assert::are_equal("  42.24", strings::format("{0,+7}", to_value<Value>(42.24)));
    }
    
    void test_method_(format_with_left_alignment_with_zero) {
      assert::are_equal("42.24", strings::format("{0,0}", to_value<Value>(42.24)));
    }
    
    void test_method_(format_with_right_alignment) {
      assert::are_equal("42.24  ", strings::format("{0,-7}", to_value<Value>(42.24)));
    }
    
    void test_method_(format_with_right_alignment_with_zero) {
      assert::are_equal("42.24", strings::format("{0,-0}", to_value<Value>(42.24)));
    }
    
    void test_method_(format_with_alignment_empty) {
      assert::are_equal("42.24", strings::format("{0,}", to_value<Value>(42.24)));
    }
    
    void test_method_(format_with_alignment_invalid) {
      assert::throws<std::invalid_argument>([]{strings::format("{0,a}", to_value<Value>(42.24));});
    }
    
    void test_method_(format_with_currency_argument) {
      assert::are_equal("$42.24", strings::format("{0:c}", to_value<Value>(42.24)));
    }
    
    void test_method_(format_with_currency_argument_and_precision) {
      assert::are_not_equal("$42.24000", strings::format("{0:C5}", to_value<Value>(42.24)), "The precision of currency format  is ignored");
      assert::are_equal("$42.24", strings::format("{0:C5}", to_value<Value>(42.24)), "The precision of currency format is ignored");
    }
    
    void test_method_(format_with_currency_argument_and_positive_precision) {
      assert::are_not_equal("$42.24000", strings::format("{0:C+5}", to_value<Value>(42.24)), "The precision of currency format  is ignored");
      assert::are_equal("$42.24", strings::format("{0:C+5}", to_value<Value>(42.24)), "The precision of currency format is ignored");
    }
    
    void test_method_(format_with_currency_argument_and_negative_precision) {
      assert::are_not_equal("$42.24000", strings::format("{0:C-5}", to_value<Value>(42.24)), "The precision of currency format  is ignored");
      assert::are_equal("$42.24", strings::format("{0:C-5}", to_value<Value>(42.24)), "The precision of currency format is ignored");
    }
    
    void test_method_(format_with_currency_argument_and_invalid_precision) {
      assert::throws<std::invalid_argument>([]{strings::format("{0:Ca}", to_value<Value>(42.24));});
    }
    
    void test_method_(format_with_exponencial_argument) {
      assert::are_equal("4.224000e+01", strings::format("{0:e}", to_value<Value>(42.24)));
    }
    
    void test_method_(format_with_exponencial_argument_and_precision) {
      if (std::is_same<Value, float>::value)
        assert::are_equal("4.2240001678E+01", strings::format("{0:E10}", to_value<Value>(42.24)));
      else
        assert::are_equal("4.2240000000E+01", strings::format("{0:E10}", to_value<Value>(42.24)));
    }
    
    void test_method_(format_with_exponencial_argument_and_positive_precision) {
      if (std::is_same<Value, float>::value)
        assert::are_equal("4.2240001678E+01", strings::format("{0:E+10}", to_value<Value>(42.24)));
      else
        assert::are_equal("4.2240000000E+01", strings::format("{0:E+10}", to_value<Value>(42.24)));
    }
    
    void test_method_(format_with_exponencial_argument_and_negative_precision) {
      assert::are_equal("4.224000E+01", strings::format("{0:E-10}", to_value<Value>(42.24)), "Negative precision for exponencial format reset precision to default (6).");
    }
    
    void test_method_(format_with_exponencial_argument_and_invalid_precision) {
      assert::throws<std::invalid_argument>([]{strings::format("{0:Ea}", to_value<Value>(42.24));});
    }
    
    void test_method_(format_with_fixed_point_argument) {
      assert::are_equal("42.24", strings::format("{0:f}", to_value<Value>(42.24)));
    }
    
    void test_method_(format_with_fixed_point_argument_and_precision) {
      assert::are_equal("42.2400", strings::format("{0:F4}", to_value<Value>(42.24)));
    }
    
    void test_method_(format_with_fixed_point_argument_and_positive_precision) {
      assert::are_equal("42.2400", strings::format("{0:F+4}", to_value<Value>(42.24)));
    }
    
    void test_method_(format_with_fixed_point_argument_and_negative_precision) {
      if (std::is_same<Value, float>::value)
        assert::are_equal("42.240002", strings::format("{0:F-4}", to_value<Value>(42.24)), "Negative precision for fixed-point format reset precision to default (6).");
      else
        assert::are_equal("42.240000", strings::format("{0:F-4}", to_value<Value>(42.24)), "Negative precision for fixed-point format reset precision to default (6).");
    }
    
    void test_method_(format_with_fixed_point_argument_and_invalid_precision) {
      assert::throws<std::invalid_argument>([]{strings::format("{0:Fa}", to_value<Value>(42.24));});
    }
    
    void test_method_(format_with_general_argument) {
      assert::are_equal("42", strings::format("{0:g}", to_value<Value>(42.0)));
    }
    
    void test_method_(format_with_decimals_with_general_argument) {
      if (std::is_same<Value, float>::value)
        assert::are_equal("42.24000168", strings::format("{0:g}", to_value<Value>(42.24)));
      else
        assert::are_equal("42.24", strings::format("{0:g}", to_value<Value>(42.24)));
    }
    
    void test_method_(format_with_general_argument_and_precision) {
      assert::are_equal("42", strings::format("{0:G4}", to_value<Value>(42.0)));
    }
    
    void test_method_(format_with_decimals_with_general_argument_and_precision) {
      assert::are_equal("42.24", strings::format("{0:G4}", to_value<Value>(42.24)));
    }
    
    void test_method_(format_with_generals_argument_and_positive_precision) {
      assert::are_equal("42", strings::format("{0:G+4}", to_value<Value>(42.0)));
    }
    
    void test_method_(format_with_decimals_with_general_argument_and_positive_precision) {
      assert::are_equal("42.24", strings::format("{0:G+4}", to_value<Value>(42.24)));
    }
    
    void test_method_(format_with_general_argument_and_negative_precision) {
      assert::are_equal("42", strings::format("{0:G-6}", to_value<Value>(42.0)));
    }
    
    void test_method_(format_with_decimals_with_general_argument_and_negative_precision) {
      assert::are_equal("42.24", strings::format("{0:G-4}", to_value<Value>(42.24)));
    }
    
    void test_method_(format_with_general_argument_and_invalid_precision) {
      assert::throws<std::invalid_argument>([]{strings::format("{0:Ga}", to_value<Value>(42.24));});
    }
    
    void test_method_(format_with_number_argument) {
      if (std::is_same<Value, float>::value)
        assert::are_equal("1,234,567.88", strings::format("{0:n}", to_value<Value>(1234567.89)));
      else
        assert::are_equal("1,234,567.89", strings::format("{0:n}", to_value<Value>(1234567.89)));
    }
    
    void test_method_(format_with_number_argument_and_precision) {
      if (std::is_same<Value, float>::value)
        assert::are_equal("1,234,567.8750", strings::format("{0:N4}", to_value<Value>(1234567.89)));
      else
        assert::are_equal("1,234,567.8900", strings::format("{0:N4}", to_value<Value>(1234567.89)));
    }
    
    void test_method_(format_with_number_argument_and_positive_precision) {
      if (std::is_same<Value, float>::value)
        assert::are_equal("1,234,567.8750", strings::format("{0:N+4}", to_value<Value>(1234567.89)));
      else
        assert::are_equal("1,234,567.8900", strings::format("{0:N+4}", to_value<Value>(1234567.89)));
    }
    
    void test_method_(format_with_number_argument_and_negative_precision) {
      if (std::is_same<Value, float>::value)
        assert::are_equal("1,234,567.875000", strings::format("{0:N-4}", to_value<Value>(1234567.89)), "Negative precision for number format reset precision to default (6).");
      else
        assert::are_equal("1,234,567.890000", strings::format("{0:N-4}", to_value<Value>(1234567.89)), "Negative precision for number format reset precision to default (6).");
    }
    
    void test_method_(format_with_number_argument_and_invalid_precision) {
      assert::throws<std::invalid_argument>([]{strings::format("{0:Na}", to_value<Value>(1234567.89));});
    }

  };
}