#ifndef RUNTIME_MATH_POINT_H
#define RUNTIME_MATH_POINT_H

/**
 * Structure for integer points in 2-d space.
 */
struct Point
{
	int32 _x;
	int32 _y;
public:
	static const Point ZeroPoint;
	static const Point NonePoint;
public:
	Point();
	Point(int32 x,int32 y);

	/**
	 * Gets specific component of a point.
	 *
	 * @param pointIndex Index of point component.
	 * @return const reference to component.
	 */
	const int32& operator()( int32 pointIndex ) const;

	/**
	 * Gets specific component of a point.
	 *
	 * @param pointIndex Index of point component
	 * @return reference to component.
	 */
	int32& operator()( int32 pointIndex );

	/**
	 * Compares points for equality.
	 *
	 * @param other The other int point being compared.
	 * @return true if the points are equal, false otherwise.
	 */
	bool operator==( const Point& other ) const;

	/**
	 * Compares points for inequality.
	 *
	 * @param other The other int point being compared.
	 * @return true if the points are not equal, false otherwise.
	 */
	bool operator!=( const Point& other ) const;

	/**
	 * Scales this point.
	 *
	 * @param scale What to multiply the point by.
	 * @return Reference to this point after multiplication.
	 */
	Point& operator*=( int32 scale );

	/**
	 * Divides this point.
	 *
	 * @param Divisor What to divide the point by.
	 * @return Reference to this point after division.
	 */
	Point& operator/=( int32 divisor );

	/**
	 * Adds to this point.
	 *
	 * @param Other The point to add to this point.
	 * @return Reference to this point after addition.
	 */
	Point& operator+=( const Point& other );
	
	/**
	 * Subtracts from this point.
	 *
	 * @param Other The point to subtract from this point.
	 * @return Reference to this point after subtraction.
	 */
	Point& operator-=( const Point& other );

	/**
	 * Divides this point.
	 *
	 * @param Other The point to divide with.
	 * @return Reference to this point after division.
	 */
	Point& operator/=( const Point& other );

	/**
	 * Assigns another point to this one.
	 *
	 * @param Other The point to assign this point from.
	 * @return Reference to this point after assignment.
	 */
	Point& operator=( const Point& other );

	/**
	 * Gets the result of scaling on this point.
	 *
	 * @param Scale What to multiply the point by.
	 * @return A new scaled int point.
	 */
	Point operator*( int32 scale) const;

	/**
	 * Gets the result of division on this point.
	 *
	 * @param Divisor What to divide the point by.
	 * @return A new divided int point.
	 */
	Point operator/( int32 divisor ) const;

	/**
	 * Gets the result of addition on this point.
	 *
	 * @param Other The other point to add to this.
	 * @return A new combined int point.
	 */
	Point operator+( const Point& other ) const;

	/**
	 * Gets the result of subtraction from this point.
	 *
	 * @param Other The other point to subtract from this.
	 * @return A new subtracted int point.
	 */
	Point operator-( const Point& other ) const;

	/**
	 * Gets the result of division on this point.
	 *
	 * @param Other The other point to subtract from this.
	 * @return A new subtracted int point.
	 */
	Point operator/( const Point& other ) const;

	/**
	* Gets specific component of the point.
	*
	* @param Index the index of point component
	* @return reference to component.
	*/
	int32& operator[](int32 index);

	/**
	* Gets specific component of the point.
	*
	* @param Index the index of point component
	* @return copy of component value.
	*/
	int32 operator[](int32 index) const;

	/** Gets the component-wise min of two vectors. */
	FORCEINLINE Point ComponentMin(const Point& other) const;

	/** Gets the component-wise max of two vectors. */
	FORCEINLINE Point ComponentMax(const Point& other) const;

public:

	/**
	 * Gets the maximum value in the point.
	 *
	 * @return The maximum value in the point.
	 * @see GetMin, Size, SizeSquared
	 */
	int32 getMax() const;

	/**
	 * Gets the minimum value in the point.
	 *
	 * @return The minimum value in the point.
	 * @see GetMax, Size, SizeSquared
	 */
	int32 getMin() const;

	/**
	 * Gets the distance of this point from (0,0).
	 *
	 * @return The distance of this point from (0,0).
	 * @see GetMax, GetMin, SizeSquared
	 */
	int32 size() const;

	/**
	 * Gets the squared distance of this point from (0,0).
	 *
	 * @return The squared distance of this point from (0,0).
	 * @see GetMax, GetMin, Size
	 */
	int32 sizeSquared() const;
	
	/**
	 * Get a textual representation of this point.
	 *
	 * @return A string describing the point.
	 */
	String toString() const;
public:

	/**
	 * Divide an int point and round up the result.
	 *
	 * @param lhs The int point being divided.
	 * @param Divisor What to divide the int point by.
	 * @return A new divided int point.
	 * @see DivideAndRoundDown
	 */
	static Point DivideAndRoundUp( Point lhs, int32 Divisor );
	static Point DivideAndRoundUp( Point lhs, Point Divisor );

	/**
	 * Divide an int point and round down the result.
	 *
	 * @param lhs The int point being divided.
	 * @param Divisor What to divide the int point by.
	 * @return A new divided int point.
	 * @see DivideAndRoundUp
	 */
	static Point DivideAndRoundDown( Point lhs, int32 Divisor );

	/**
	 * Gets number of components point has.
	 * @return number of components point has.
	 */
	static int32 Num();

public:

	/**
	 * Serializes the point.
	 *
	 * @param Ar The archive to serialize into.
	 * @param Point The point to serialize.
	 * @return Reference to the Archive after serialization.
	 */
	friend Archive& operator<<( Archive& archive, Point& Point )
	{
		return archive << Point.X << Point.Y;
	}
}


#endif
