package platform

import (
	"testing"
)

func TestBigIntBasic(t *testing.T) {
	if err := Init(); err != nil {
		t.Fatalf("Init() failed: %v", err)
	}
	defer Cleanup()

	lhs, err := ParseBigInt("12345678901234567890")
	if err != nil {
		t.Fatalf("ParseBigInt(lhs) failed: %v", err)
	}
	defer lhs.Destroy()

	rhs, err := ParseBigInt("10")
	if err != nil {
		t.Fatalf("ParseBigInt(rhs) failed: %v", err)
	}
	defer rhs.Destroy()

	result, err := NewBigInt()
	if err != nil {
		t.Fatalf("NewBigInt() failed: %v", err)
	}
	defer result.Destroy()

	if err := result.Add(lhs, rhs); err != nil {
		t.Fatalf("Add() failed: %v", err)
	}
	if got := result.String(); got != "12345678901234567900" {
		t.Fatalf("Add() = %q", got)
	}

	if err := result.Sub(lhs, rhs); err != nil {
		t.Fatalf("Sub() failed: %v", err)
	}
	if got := result.String(); got != "12345678901234567880" {
		t.Fatalf("Sub() = %q", got)
	}

	if err := result.Mul(rhs, rhs); err != nil {
		t.Fatalf("Mul() failed: %v", err)
	}
	if got := result.String(); got != "100" {
		t.Fatalf("Mul() = %q", got)
	}

	if err := result.Div(lhs, rhs); err != nil {
		t.Fatalf("Div() failed: %v", err)
	}
	if got := result.String(); got != "1234567890123456789" {
		t.Fatalf("Div() = %q", got)
	}

	if err := result.Mod(lhs, rhs); err != nil {
		t.Fatalf("Mod() failed: %v", err)
	}
	if got := result.String(); got != "0" {
		t.Fatalf("Mod() = %q", got)
	}
}

func TestBigIntErrors(t *testing.T) {
	if err := Init(); err != nil {
		t.Fatalf("Init() failed: %v", err)
	}
	defer Cleanup()

	value, err := NewBigInt()
	if err != nil {
		t.Fatalf("NewBigInt() failed: %v", err)
	}
	defer value.Destroy()

	if err := value.SetString("abc"); err == nil {
		t.Fatal("SetString() expected parse error")
	}

	zero, err := NewBigInt()
	if err != nil {
		t.Fatalf("NewBigInt(zero) failed: %v", err)
	}
	defer zero.Destroy()

	if err := zero.SetInt64(0); err != nil {
		t.Fatalf("zero.SetInt64() failed: %v", err)
	}
	if err := value.SetInt64(7); err != nil {
		t.Fatalf("value.SetInt64() failed: %v", err)
	}

	if err := value.Div(value, zero); err == nil {
		t.Fatal("Div() expected divide-by-zero error")
	}
}

func TestBigIntUint64Overflow(t *testing.T) {
	if err := Init(); err != nil {
		t.Fatalf("Init() failed: %v", err)
	}
	defer Cleanup()

	value, err := ParseBigInt("18446744073709551616")
	if err != nil {
		t.Fatalf("ParseBigInt() failed: %v", err)
	}
	defer value.Destroy()

	if _, err := value.Uint64(); err == nil {
		t.Fatal("Uint64() expected overflow error")
	}
}

// Test: 1024-bit large numbers
func TestBigIntLarge1024Bit(t *testing.T) {
	if err := Init(); err != nil {
		t.Fatalf("Init() failed: %v", err)
	}
	defer Cleanup()

	// 2^1000
	largeNum := "10715086071862673209484250490600018105614048117055336074437503883703510511249361224931983788156958581275946729175531468251871452856923140435984577574698574803934567774824230985421074605062371141877954182153046474983581941267398767559165543946077062914571196477686542167660429831652624386837205668069376"

	a, err := ParseBigInt(largeNum)
	if err != nil {
		t.Fatalf("ParseBigInt() failed: %v", err)
	}
	defer a.Destroy()

	two, err := NewBigInt()
	if err != nil {
		t.Fatalf("NewBigInt() failed: %v", err)
	}
	defer two.Destroy()
	two.SetInt64(2)

	result, err := NewBigInt()
	if err != nil {
		t.Fatalf("NewBigInt() failed: %v", err)
	}
	defer result.Destroy()

	// Multiply by 2
	if err := result.Mul(a, two); err != nil {
		t.Fatalf("Mul() failed: %v", err)
	}

	// Divide back by 2
	if err := result.Div(result, two); err != nil {
		t.Fatalf("Div() failed: %v", err)
	}

	// Should match original
	if result.String() != largeNum {
		t.Fatalf("Large number arithmetic failed: got %s, want %s", result.String(), largeNum)
	}
}

// Test: 2048-bit very large numbers
func TestBigIntLarge2048Bit(t *testing.T) {
	if err := Init(); err != nil {
		t.Fatalf("Init() failed: %v", err)
	}
	defer Cleanup()

	// 2^2000
	hugeNum := "114813069527425452423283320117768198402231770208869520047764273682576626139237031385665948631650626991844596463898746277344711896086305533142593135616665318539129989145312280000688779148240044871428926990063486244781615463646388363947317026040466353970904996558162398808944629605623311649536164221970332681344168908984458505602379484807914058900934776500429002716706625830522008132236281291761267883317206598995396418127021779858404042159853183251540889433902091920554957783589672039160081957216630582755380425583726015528348786419432054508915275783882625175435528800822842770817965453762184851149029376"

	a, err := ParseBigInt(hugeNum)
	if err != nil {
		t.Fatalf("ParseBigInt() failed: %v", err)
	}
	defer a.Destroy()

	one, err := NewBigInt()
	if err != nil {
		t.Fatalf("NewBigInt() failed: %v", err)
	}
	defer one.Destroy()
	one.SetInt64(1)

	result, err := NewBigInt()
	if err != nil {
		t.Fatalf("NewBigInt() failed: %v", err)
	}
	defer result.Destroy()

	// Add 1
	if err := result.Add(a, one); err != nil {
		t.Fatalf("Add() failed: %v", err)
	}

	// Subtract 1
	if err := result.Sub(result, one); err != nil {
		t.Fatalf("Sub() failed: %v", err)
	}

	// Should match original
	if result.String() != hugeNum {
		t.Fatalf("Very large number arithmetic failed")
	}
}

// Test: Factorial computation (50!)
func TestBigIntFactorial(t *testing.T) {
	if err := Init(); err != nil {
		t.Fatalf("Init() failed: %v", err)
	}
	defer Cleanup()

	result, err := NewBigInt()
	if err != nil {
		t.Fatalf("NewBigInt() failed: %v", err)
	}
	defer result.Destroy()
	result.SetInt64(1)

	i, err := NewBigInt()
	if err != nil {
		t.Fatalf("NewBigInt() failed: %v", err)
	}
	defer i.Destroy()

	temp, err := NewBigInt()
	if err != nil {
		t.Fatalf("NewBigInt() failed: %v", err)
	}
	defer temp.Destroy()

	// Compute 50!
	for n := int64(2); n <= 50; n++ {
		i.SetInt64(n)
		if err := temp.Mul(result, i); err != nil {
			t.Fatalf("Mul() failed at n=%d: %v", n, err)
		}
		if err := result.SetString(temp.String()); err != nil {
			t.Fatalf("SetString() failed: %v", err)
		}
	}

	// 50! = 30414093201713378043612608166064768844377641568960512000000000000
	expected := "30414093201713378043612608166064768844377641568960512000000000000"
	if result.String() != expected {
		t.Fatalf("Factorial(50) = %s, want %s", result.String(), expected)
	}
}

// Test: Fibonacci sequence
func TestBigIntFibonacci(t *testing.T) {
	if err := Init(); err != nil {
		t.Fatalf("Init() failed: %v", err)
	}
	defer Cleanup()

	a, err := NewBigInt()
	if err != nil {
		t.Fatalf("NewBigInt() failed: %v", err)
	}
	defer a.Destroy()
	a.SetInt64(0)

	b, err := NewBigInt()
	if err != nil {
		t.Fatalf("NewBigInt() failed: %v", err)
	}
	defer b.Destroy()
	b.SetInt64(1)

	temp, err := NewBigInt()
	if err != nil {
		t.Fatalf("NewBigInt() failed: %v", err)
	}
	defer temp.Destroy()

	// Compute Fibonacci(200)
	for i := 0; i < 200; i++ {
		if err := temp.Add(a, b); err != nil {
			t.Fatalf("Add() failed at i=%d: %v", i, err)
		}
		// Copy b to a
		aStr := b.String()
		if err := a.SetString(aStr); err != nil {
			t.Fatalf("SetString(a) failed: %v", err)
		}
		// Copy temp to b
		bStr := temp.String()
		if err := b.SetString(bStr); err != nil {
			t.Fatalf("SetString(b) failed: %v", err)
		}
	}

	// Fib(200) = 453973694165307953197296969697410619233826
	expected := "453973694165307953197296969697410619233826"
	if b.String() != expected {
		t.Fatalf("Fibonacci(200) = %s, want %s", b.String(), expected)
	}
}

// Test: Power of 2 (2^512)
func TestBigIntPowerOf2(t *testing.T) {
	if err := Init(); err != nil {
		t.Fatalf("Init() failed: %v", err)
	}
	defer Cleanup()

	result, err := NewBigInt()
	if err != nil {
		t.Fatalf("NewBigInt() failed: %v", err)
	}
	defer result.Destroy()
	result.SetInt64(1)

	two, err := NewBigInt()
	if err != nil {
		t.Fatalf("NewBigInt() failed: %v", err)
	}
	defer two.Destroy()
	two.SetInt64(2)

	temp, err := NewBigInt()
	if err != nil {
		t.Fatalf("NewBigInt() failed: %v", err)
	}
	defer temp.Destroy()

	// Compute 2^512
	for i := 0; i < 512; i++ {
		if err := temp.Mul(result, two); err != nil {
			t.Fatalf("Mul() failed at i=%d: %v", i, err)
		}
		result.SetString(temp.String())
	}

	// 2^512
	expected := "13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084096"
	if result.String() != expected {
		t.Fatalf("2^512 = %s, want %s", result.String(), expected)
	}
}

// Test: Negative number arithmetic
func TestBigIntNegativeArithmetic(t *testing.T) {
	if err := Init(); err != nil {
		t.Fatalf("Init() failed: %v", err)
	}
	defer Cleanup()

	a, err := NewBigInt()
	if err != nil {
		t.Fatalf("NewBigInt() failed: %v", err)
	}
	defer a.Destroy()
	a.SetInt64(-100)

	b, err := NewBigInt()
	if err != nil {
		t.Fatalf("NewBigInt() failed: %v", err)
	}
	defer b.Destroy()
	b.SetInt64(-50)

	result, err := NewBigInt()
	if err != nil {
		t.Fatalf("NewBigInt() failed: %v", err)
	}
	defer result.Destroy()

	// -100 + (-50) = -150
	if err := result.Add(a, b); err != nil {
		t.Fatalf("Add() failed: %v", err)
	}
	if val, _ := result.Int64(); val != -150 {
		t.Fatalf("Add() = %d, want -150", val)
	}

	// -100 - (-50) = -50
	if err := result.Sub(a, b); err != nil {
		t.Fatalf("Sub() failed: %v", err)
	}
	if val, _ := result.Int64(); val != -50 {
		t.Fatalf("Sub() = %d, want -50", val)
	}

	// -100 * (-50) = 5000
	if err := result.Mul(a, b); err != nil {
		t.Fatalf("Mul() failed: %v", err)
	}
	if val, _ := result.Int64(); val != 5000 {
		t.Fatalf("Mul() = %d, want 5000", val)
	}

	// -100 / (-50) = 2
	if err := result.Div(a, b); err != nil {
		t.Fatalf("Div() failed: %v", err)
	}
	if val, _ := result.Int64(); val != 2 {
		t.Fatalf("Div() = %d, want 2", val)
	}
}

// Test: Neg and Abs operations
func TestBigIntNegAbs(t *testing.T) {
	if err := Init(); err != nil {
		t.Fatalf("Init() failed: %v", err)
	}
	defer Cleanup()

	value, err := NewBigInt()
	if err != nil {
		t.Fatalf("NewBigInt() failed: %v", err)
	}
	defer value.Destroy()
	value.SetInt64(42)

	result, err := NewBigInt()
	if err != nil {
		t.Fatalf("NewBigInt() failed: %v", err)
	}
	defer result.Destroy()

	// Neg(42) = -42
	if err := result.Neg(value); err != nil {
		t.Fatalf("Neg() failed: %v", err)
	}
	if val, _ := result.Int64(); val != -42 {
		t.Fatalf("Neg() = %d, want -42", val)
	}

	// Abs(-42) = 42
	if err := result.Abs(result); err != nil {
		t.Fatalf("Abs() failed: %v", err)
	}
	if val, _ := result.Int64(); val != 42 {
		t.Fatalf("Abs() = %d, want 42", val)
	}
}

// Test: Comparison operations
func TestBigIntComparison(t *testing.T) {
	if err := Init(); err != nil {
		t.Fatalf("Init() failed: %v", err)
	}
	defer Cleanup()

	a, err := ParseBigInt("1000000000000000000000")
	if err != nil {
		t.Fatalf("ParseBigInt() failed: %v", err)
	}
	defer a.Destroy()

	b, err := ParseBigInt("999999999999999999999")
	if err != nil {
		t.Fatalf("ParseBigInt() failed: %v", err)
	}
	defer b.Destroy()

	// a > b
	if cmp, err := a.Cmp(b); err != nil || cmp <= 0 {
		t.Fatalf("Cmp() = %d, want > 0", cmp)
	}

	// b < a
	if cmp, err := b.Cmp(a); err != nil || cmp >= 0 {
		t.Fatalf("Cmp() = %d, want < 0", cmp)
	}

	// a == a
	if cmp, err := a.Cmp(a); err != nil || cmp != 0 {
		t.Fatalf("Cmp() = %d, want 0", cmp)
	}
}

// Test: String parsing edge cases
func TestBigIntStringEdgeCases(t *testing.T) {
	if err := Init(); err != nil {
		t.Fatalf("Init() failed: %v", err)
	}
	defer Cleanup()

	value, err := NewBigInt()
	if err != nil {
		t.Fatalf("NewBigInt() failed: %v", err)
	}
	defer value.Destroy()

	// Leading zeros
	if err := value.SetString("00042"); err != nil {
		t.Fatalf("SetString(00042) failed: %v", err)
	}
	if val, _ := value.Int64(); val != 42 {
		t.Fatalf("SetString(00042) = %d, want 42", val)
	}

	// Negative with leading zeros
	if err := value.SetString("-00042"); err != nil {
		t.Fatalf("SetString(-00042) failed: %v", err)
	}
	if val, _ := value.Int64(); val != -42 {
		t.Fatalf("SetString(-00042) = %d, want -42", val)
	}

	// Just zero
	if err := value.SetString("0"); err != nil {
		t.Fatalf("SetString(0) failed: %v", err)
	}
	if val, _ := value.Int64(); val != 0 {
		t.Fatalf("SetString(0) = %d, want 0", val)
	}

	// Invalid: empty string
	if err := value.SetString(""); err == nil {
		t.Fatal("SetString() expected error for empty string")
	}

	// Invalid: only sign
	if err := value.SetString("-"); err == nil {
		t.Fatal("SetString() expected error for only sign")
	}

	// Invalid: mixed characters
	if err := value.SetString("123abc"); err == nil {
		t.Fatal("SetString() expected error for mixed characters")
	}
}

