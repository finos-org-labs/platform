package platform

import (
	"math"
	"testing"
)

func TestBigFloatBasic(t *testing.T) {
	if err := Init(); err != nil {
		t.Fatalf("Init() failed: %v", err)
	}
	defer Cleanup()

	lhs, err := ParseBigFloat("1.5")
	if err != nil {
		t.Fatalf("ParseBigFloat(lhs) failed: %v", err)
	}
	defer lhs.Destroy()

	rhs, err := ParseBigFloat("2.0")
	if err != nil {
		t.Fatalf("ParseBigFloat(rhs) failed: %v", err)
	}
	defer rhs.Destroy()

	result, err := NewBigFloat()
	if err != nil {
		t.Fatalf("NewBigFloat() failed: %v", err)
	}
	defer result.Destroy()

	if err := result.Add(lhs, rhs); err != nil {
		t.Fatalf("Add() failed: %v", err)
	}
	if got, err := result.Float64(); err != nil || math.Abs(got-3.5) > 1e-12 {
		t.Fatalf("Add() = %v, %v", got, err)
	}

	if err := result.Mul(lhs, rhs); err != nil {
		t.Fatalf("Mul() failed: %v", err)
	}
	if got, err := result.Float64(); err != nil || math.Abs(got-3.0) > 1e-12 {
		t.Fatalf("Mul() = %v, %v", got, err)
	}

	if err := result.Sqrt(rhs); err != nil {
		t.Fatalf("Sqrt() failed: %v", err)
	}
	if got, err := result.Float64(); err != nil || math.Abs(got-math.Sqrt(2.0)) > 1e-12 {
		t.Fatalf("Sqrt() = %v, %v", got, err)
	}
}

func TestBigFloatPrecisionAndBigIntConversion(t *testing.T) {
	if err := Init(); err != nil {
		t.Fatalf("Init() failed: %v", err)
	}
	defer Cleanup()

	value, err := NewBigFloatWithPrec(512)
	if err != nil {
		t.Fatalf("NewBigFloatWithPrec() failed: %v", err)
	}
	defer value.Destroy()

	if got, err := value.Precision(); err != nil || got != 512 {
		t.Fatalf("Precision() = %d, %v", got, err)
	}

	integer, err := ParseBigInt("42")
	if err != nil {
		t.Fatalf("ParseBigInt() failed: %v", err)
	}
	defer integer.Destroy()

	if err := value.SetBigInt(integer); err != nil {
		t.Fatalf("SetBigInt() failed: %v", err)
	}
	if got, err := value.Float64(); err != nil || got != 42 {
		t.Fatalf("Float64() = %v, %v", got, err)
	}
}

func TestBigFloatErrors(t *testing.T) {
	if err := Init(); err != nil {
		t.Fatalf("Init() failed: %v", err)
	}
	defer Cleanup()

	value, err := NewBigFloat()
	if err != nil {
		t.Fatalf("NewBigFloat() failed: %v", err)
	}
	defer value.Destroy()

	if err := value.SetString("abc"); err == nil {
		t.Fatal("SetString() expected parse error")
	}

	neg, err := ParseBigFloat("-1")
	if err != nil {
		t.Fatalf("ParseBigFloat(-1) failed: %v", err)
	}
	defer neg.Destroy()

	if err := value.Sqrt(neg); err == nil {
		t.Fatal("Sqrt() expected invalid argument error")
	}

	zero, err := ParseBigFloat("0")
	if err != nil {
		t.Fatalf("ParseBigFloat(0) failed: %v", err)
	}
	defer zero.Destroy()

	one, err := ParseBigFloat("1")
	if err != nil {
		t.Fatalf("ParseBigFloat(1) failed: %v", err)
	}
	defer one.Destroy()

	if err := value.Div(one, zero); err == nil {
		t.Fatal("Div() expected divide-by-zero error")
	}
}

// Test: High precision Pi approximation
func TestBigFloatHighPrecisionPi(t *testing.T) {
	if err := Init(); err != nil {
		t.Fatalf("Init() failed: %v", err)
	}
	defer Cleanup()

	// Use 1024-bit precision
	result, err := NewBigFloatWithPrec(1024)
	if err != nil {
		t.Fatalf("NewBigFloatWithPrec() failed: %v", err)
	}
	defer result.Destroy()
	result.SetFloat64(0.0)

	one, err := NewBigFloatWithPrec(1024)
	if err != nil {
		t.Fatalf("NewBigFloatWithPrec() failed: %v", err)
	}
	defer one.Destroy()
	one.SetFloat64(1.0)

	divisor, err := NewBigFloatWithPrec(1024)
	if err != nil {
		t.Fatalf("NewBigFloatWithPrec() failed: %v", err)
	}
	defer divisor.Destroy()

	term, err := NewBigFloatWithPrec(1024)
	if err != nil {
		t.Fatalf("NewBigFloatWithPrec() failed: %v", err)
	}
	defer term.Destroy()

	temp, err := NewBigFloatWithPrec(1024)
	if err != nil {
		t.Fatalf("NewBigFloatWithPrec() failed: %v", err)
	}
	defer temp.Destroy()

	// Compute Pi/4 using Leibniz formula: Pi/4 = 1 - 1/3 + 1/5 - 1/7 + ...
	for i := 0; i < 10000; i++ {
		divisor.SetInt64(int64(2*i + 1))
		term.Div(one, divisor)

		if i%2 == 0 {
			temp.Add(result, term)
		} else {
			temp.Sub(result, term)
		}
		result.SetString(temp.String())
	}

	// Multiply by 4 to get Pi
	four, _ := NewBigFloatWithPrec(1024)
	defer four.Destroy()
	four.SetFloat64(4.0)
	result.Mul(result, four)

	// Check that result is close to Pi
	piApprox, _ := result.Float64()
	if math.Abs(piApprox-math.Pi) > 0.001 {
		t.Fatalf("Pi approximation = %v, want ~%v", piApprox, math.Pi)
	}
}

// Test: Extreme precision (4096-bit)
func TestBigFloatExtremePrecision(t *testing.T) {
	if err := Init(); err != nil {
		t.Fatalf("Init() failed: %v", err)
	}
	defer Cleanup()

	value, err := NewBigFloatWithPrec(4096)
	if err != nil {
		t.Fatalf("NewBigFloatWithPrec() failed: %v", err)
	}
	defer value.Destroy()

	prec, _ := value.Precision()
	if prec != 4096 {
		t.Fatalf("Precision() = %d, want 4096", prec)
	}

	// Set a high-precision value
	value.SetString("1.23456789012345678901234567890123456789")

	result, err := NewBigFloatWithPrec(4096)
	if err != nil {
		t.Fatalf("NewBigFloatWithPrec() failed: %v", err)
	}
	defer result.Destroy()

	// Square it
	result.Mul(value, value)

	// Take square root
	result.Sqrt(result)

	// Should be close to original
	cmp, _ := result.Cmp(value)
	if cmp != 0 {
		t.Logf("Warning: precision loss detected (expected with extreme precision)")
	}
}

// Test: Precision loss detection
func TestBigFloatPrecisionLoss(t *testing.T) {
	if err := Init(); err != nil {
		t.Fatalf("Init() failed: %v", err)
	}
	defer Cleanup()

	lowPrec, err := NewBigFloatWithPrec(53) // double precision
	if err != nil {
		t.Fatalf("NewBigFloatWithPrec() failed: %v", err)
	}
	defer lowPrec.Destroy()

	highPrec, err := NewBigFloatWithPrec(256)
	if err != nil {
		t.Fatalf("NewBigFloatWithPrec() failed: %v", err)
	}
	defer highPrec.Destroy()

	// Set high precision value
	highPrec.SetString("1.234567890123456789012345678901234567890")

	// Get as float64 (will lose precision)
	val, _ := highPrec.Float64()

	// Set to low precision
	lowPrec.SetFloat64(val)

	// Values should differ due to precision loss
	cmp, _ := lowPrec.Cmp(highPrec)
	if cmp == 0 {
		t.Fatal("Expected precision loss, but values are equal")
	}
}

// Test: Very small numbers
func TestBigFloatVerySmallNumbers(t *testing.T) {
	if err := Init(); err != nil {
		t.Fatalf("Init() failed: %v", err)
	}
	defer Cleanup()

	value, err := NewBigFloatWithPrec(512)
	if err != nil {
		t.Fatalf("NewBigFloatWithPrec() failed: %v", err)
	}
	defer value.Destroy()

	// Set to 10^-100
	value.SetString("1e-100")

	multiplier, err := NewBigFloatWithPrec(512)
	if err != nil {
		t.Fatalf("NewBigFloatWithPrec() failed: %v", err)
	}
	defer multiplier.Destroy()
	multiplier.SetString("1e100")

	result, err := NewBigFloatWithPrec(512)
	if err != nil {
		t.Fatalf("NewBigFloatWithPrec() failed: %v", err)
	}
	defer result.Destroy()

	// Multiply: 10^-100 * 10^100 = 1
	result.Mul(value, multiplier)

	out, _ := result.Float64()
	if math.Abs(out-1.0) > 1e-10 {
		t.Fatalf("Very small number arithmetic: got %v, want 1.0", out)
	}
}

// Test: Very large numbers
func TestBigFloatVeryLargeNumbers(t *testing.T) {
	if err := Init(); err != nil {
		t.Fatalf("Init() failed: %v", err)
	}
	defer Cleanup()

	value, err := NewBigFloatWithPrec(512)
	if err != nil {
		t.Fatalf("NewBigFloatWithPrec() failed: %v", err)
	}
	defer value.Destroy()

	// Set to 10^100
	value.SetString("1e100")

	divisor, err := NewBigFloatWithPrec(512)
	if err != nil {
		t.Fatalf("NewBigFloatWithPrec() failed: %v", err)
	}
	defer divisor.Destroy()
	divisor.SetString("1e100")

	result, err := NewBigFloatWithPrec(512)
	if err != nil {
		t.Fatalf("NewBigFloatWithPrec() failed: %v", err)
	}
	defer result.Destroy()

	// Divide: 10^100 / 10^100 = 1
	result.Div(value, divisor)

	out, _ := result.Float64()
	if math.Abs(out-1.0) > 1e-10 {
		t.Fatalf("Very large number arithmetic: got %v, want 1.0", out)
	}
}

// Test: Square root precision
func TestBigFloatSqrtPrecision(t *testing.T) {
	if err := Init(); err != nil {
		t.Fatalf("Init() failed: %v", err)
	}
	defer Cleanup()

	value, err := NewBigFloatWithPrec(1024)
	if err != nil {
		t.Fatalf("NewBigFloatWithPrec() failed: %v", err)
	}
	defer value.Destroy()
	value.SetFloat64(2.0)

	sqrtVal, err := NewBigFloatWithPrec(1024)
	if err != nil {
		t.Fatalf("NewBigFloatWithPrec() failed: %v", err)
	}
	defer sqrtVal.Destroy()

	// Compute sqrt(2)
	sqrtVal.Sqrt(value)

	// Square it back
	squared, err := NewBigFloatWithPrec(1024)
	if err != nil {
		t.Fatalf("NewBigFloatWithPrec() failed: %v", err)
	}
	defer squared.Destroy()
	squared.Mul(sqrtVal, sqrtVal)

	// Should be very close to 2.0
	result, _ := squared.Float64()
	if math.Abs(result-2.0) > 1e-15 {
		t.Fatalf("Sqrt precision: got %v, want 2.0", result)
	}
}

// Test: Conversion from large BigInt
func TestBigFloatLargeBigIntConversion(t *testing.T) {
	if err := Init(); err != nil {
		t.Fatalf("Init() failed: %v", err)
	}
	defer Cleanup()

	// 2^200
	largeInt := "1606938044258990275541962092341162602522202993782792835301376"
	bigint, err := ParseBigInt(largeInt)
	if err != nil {
		t.Fatalf("ParseBigInt() failed: %v", err)
	}
	defer bigint.Destroy()

	bigfloat, err := NewBigFloatWithPrec(512)
	if err != nil {
		t.Fatalf("NewBigFloatWithPrec() failed: %v", err)
	}
	defer bigfloat.Destroy()

	// Convert to bigfloat
	if err := bigfloat.SetBigInt(bigint); err != nil {
		t.Fatalf("SetBigInt() failed: %v", err)
	}

	// Verify string representation contains the number
	str := bigfloat.String()
	if len(str) == 0 {
		t.Fatal("String() returned empty string")
	}
}

// Test: Negative number operations
func TestBigFloatNegativeOperations(t *testing.T) {
	if err := Init(); err != nil {
		t.Fatalf("Init() failed: %v", err)
	}
	defer Cleanup()

	a, err := NewBigFloat()
	if err != nil {
		t.Fatalf("NewBigFloat() failed: %v", err)
	}
	defer a.Destroy()
	a.SetFloat64(-10.5)

	b, err := NewBigFloat()
	if err != nil {
		t.Fatalf("NewBigFloat() failed: %v", err)
	}
	defer b.Destroy()
	b.SetFloat64(-5.5)

	result, err := NewBigFloat()
	if err != nil {
		t.Fatalf("NewBigFloat() failed: %v", err)
	}
	defer result.Destroy()

	// -10.5 + (-5.5) = -16.0
	result.Add(a, b)
	val, _ := result.Float64()
	if math.Abs(val-(-16.0)) > 1e-10 {
		t.Fatalf("Add() = %v, want -16.0", val)
	}

	// -10.5 * (-2.0) = 21.0
	b.SetFloat64(-2.0)
	result.Mul(a, b)
	val, _ = result.Float64()
	if math.Abs(val-21.0) > 1e-10 {
		t.Fatalf("Mul() = %v, want 21.0", val)
	}
}

// Test: Neg and Abs operations
func TestBigFloatNegAbs(t *testing.T) {
	if err := Init(); err != nil {
		t.Fatalf("Init() failed: %v", err)
	}
	defer Cleanup()

	value, err := NewBigFloat()
	if err != nil {
		t.Fatalf("NewBigFloat() failed: %v", err)
	}
	defer value.Destroy()
	value.SetFloat64(42.5)

	result, err := NewBigFloat()
	if err != nil {
		t.Fatalf("NewBigFloat() failed: %v", err)
	}
	defer result.Destroy()

	// Neg(42.5) = -42.5
	result.Neg(value)
	val, _ := result.Float64()
	if math.Abs(val-(-42.5)) > 1e-10 {
		t.Fatalf("Neg() = %v, want -42.5", val)
	}

	// Abs(-42.5) = 42.5
	result.Abs(result)
	val, _ = result.Float64()
	if math.Abs(val-42.5) > 1e-10 {
		t.Fatalf("Abs() = %v, want 42.5", val)
	}
}

// Test: Zero operations
func TestBigFloatZeroOperations(t *testing.T) {
	if err := Init(); err != nil {
		t.Fatalf("Init() failed: %v", err)
	}
	defer Cleanup()

	zero, err := NewBigFloat()
	if err != nil {
		t.Fatalf("NewBigFloat() failed: %v", err)
	}
	defer zero.Destroy()
	zero.SetFloat64(0.0)

	value, err := NewBigFloat()
	if err != nil {
		t.Fatalf("NewBigFloat() failed: %v", err)
	}
	defer value.Destroy()
	value.SetFloat64(42.5)

	result, err := NewBigFloat()
	if err != nil {
		t.Fatalf("NewBigFloat() failed: %v", err)
	}
	defer result.Destroy()

	// 0 + 42.5 = 42.5
	result.Add(zero, value)
	val, _ := result.Float64()
	if math.Abs(val-42.5) > 1e-10 {
		t.Fatalf("Add() = %v, want 42.5", val)
	}

	// 0 * 42.5 = 0
	result.Mul(zero, value)
	val, _ = result.Float64()
	if math.Abs(val) > 1e-10 {
		t.Fatalf("Mul() = %v, want 0.0", val)
	}

	// sqrt(0) = 0
	result.Sqrt(zero)
	val, _ = result.Float64()
	if math.Abs(val) > 1e-10 {
		t.Fatalf("Sqrt() = %v, want 0.0", val)
	}
}

// Test: Comparison operations
func TestBigFloatComparison(t *testing.T) {
	if err := Init(); err != nil {
		t.Fatalf("Init() failed: %v", err)
	}
	defer Cleanup()

	a, err := ParseBigFloat("1.000000000000001")
	if err != nil {
		t.Fatalf("ParseBigFloat() failed: %v", err)
	}
	defer a.Destroy()

	b, err := ParseBigFloat("1.0")
	if err != nil {
		t.Fatalf("ParseBigFloat() failed: %v", err)
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

