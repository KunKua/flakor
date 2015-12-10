#ifndef RUNTIME_LANG_VARIANTTYPES_H
#define RUNTIME_LANG_VARIANTTYPES_H

/**
 * Enumerates the built-in types that can be stored in instances of Variant.
 */
namespace VariantTypes
{
	const int32 Empty = 0;
	const int32 Ansichar = 1;
	const int32 Bool = 2;
	const int32 Box = 3;
	const int32 BoxSphereBounds = 4;
	const int32 ByteArray = 5;
	const int32 Color = 6;
	const int32 DateTime = 7;
	const int32 Double = 8;
	const int32 Enum = 9;
	const int32 Float = 10;
	const int32 Guid = 11;
	const int32 Int8 = 12;
	const int32 Int16 = 13;
	const int32 Int32 = 14;
	const int32 Int64 = 15;
	const int32 IntRect = 16;
	const int32 LinearColor = 17;
	const int32 Matrix = 18;
	const int32 Name = 19;
	const int32 Plane = 20;
	const int32 Quat = 21;
	const int32 RandomStream = 22;
	const int32 Rotator = 23;
	const int32 String = 24;
	const int32 Widechar = 25;
	const int32 Timespan = 26;
	const int32 Transform = 27;
	const int32 TwoVectors = 28;
	const int32 UInt8 = 29;
	const int32 UInt16 = 30;
	const int32 UInt32 = 31;
	const int32 UInt64 = 32;
	const int32 Vector = 33;
	const int32 Vector2d = 34;
	const int32 Vector4 = 35;
	const int32 IntPoint = 36;
	const int32 IntVector = 37;
	const int32 NetworkGUID = 38;

	const int32 Custom = 0x40;
}

/**
 * Stub for variant type traits.
 *
 * Actual type traits need to be declared through template specialization for custom
 * data types that are to be used in FVariant. Traits for the most commonly used built-in
 * types are declared below.
 *
 * Complex types, such as structures and classes can be serialized into a byte array
 * and then assigned to a variant. Note that you will be responsible for ensuring
 * correct byte ordering when serializing those types.
 *
 * @param T The type to be used in Variant.
 */
template<typename T> struct VariantTraits
{
	static int32 getType()
	{
		static_assert(!sizeof(T), "Variant trait must be specialized for this type.");
		return VariantTypes::Empty;
	}
};

class Variant
{
public:
	/** default constructor*/
	Variant();
	/** copy constructor*/
	Variant(const Variant& other);
public:
	void empty();
	bool isEmpty() const;
	int32 getType() const
	{
		return _type;
	}

	int32 getSize() const;
	const Array<uint8>& getBytes() const;
private:
	/** Holds the type of the variant. */
	int32 _type;
	/** Holds the serialized value. */
	Array<uint8> _value;
}
