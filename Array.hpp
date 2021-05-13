#ifndef ASSIGNMENT4_ARRAY_HPP
#define ASSIGNMENT4_ARRAY_HPP

#include <exception>

namespace cs540
{
	struct OutOfRange : public std::exception
	{
		const char *what() const throw()
		{
			return "Array Out of Range Error";
		}
	};

	template <typename T, std::size_t... Dims>
	class Array
	{
		public:
			class FirstDimensionMajorIterator;
			class LastDimensionMajorIterator;
			std::size_t arraySize;
			static T ValueType;
			Array<T, Dims...> *array;
			
			//Default Constructor
			Array()
			{
		
			}

			//Copy Constructor
			Array(const Array &toCopy)
			{
				
			}

			//Copy Consturctor (Templated)
			template <typename U>
			Array(const Array<U, Dims...> &toCopyTemplated)
			{
					
			}

			//Assignment Operator
			Array &operator=(const Array &assignment)
			{
				return nullptr;
			}

			//Assignment Operator (Templated)
			template <typename U>
			Array &operator=(const Array<U, Dims...> &)
			{
				return nullptr;
			}

			T &operator[](std::size_t i)
			{
				return nullptr;
			}
			
			const T &operator[](std::size_t i)
			{
				return nullptr;			
			}


			//Iterators

			FirstDimensionMajorIterator fmbegin()
			{

			}

			FirstDimensionMajorIterator fmend()
			{
		
			}

			LastDimensionMajorIterator lmbegin()
			{

			}

			LastDimensionMajorIterator lmend()
			{
			
			}

			class FirstDimensionIterator	
			{
				public:
					std::size_t size, currentIndex;
					bool isEndIndex;
					Array<T, Dims...> *array;
					typename Array<T, Dims...>::FirstDimensionMajorIterator lowOrderIterator;
				
				public:
	
				FirstDimensionMajorIterator()
				{
			
				}

				FirstDimensionMajorIterator(const FirstDimensionMajorIterator &toCopy)
				{
			
				}

				FirstDimensionMajorIterator &operator=(const FirstDimensionMajorIterator &toAssign)
				{
				
				}


				bool operator==(const FirstDimensionMajorIterator &a, const FirstDimensionMajorIterator b)
				{
					return true;
				}
				
				bool operator!=(const FirstDimensionMajorIterator &a, const FirstDimensionMajorIterator b)
				{
					return false;
				}
				
				FirstDimensionIterator &operator++()
				{

				}
	
				FirstDimensionIterator operator++(int toIncrease)
				{
		

				}

				T &operator*() const
				{
					return nullptr;
				}
			};
	
			class LastDimensionMajorIterator
			{
				LastDimensionMajorIterator()
				{
					
				}

				LastDimensionMajorIterator(const LastDimensionMajorIterator &toCopy)
				{
			
				}
				
				LastDimensionMajorIterator(const LastDimensionMajorIterator &toAssign)
				{
				
				}
				
				bool operator==(const LastDimensionMajorIterator a, const LastDimensionMajorIterator b)
				{
					return true;
				}
			
				bool operator!=(const LastDimensionMajorIterator a, const LastDimensionMajorIterator b)
				{
					return false;
				}
				
				LastDimensionMajorIterator &operator++()
				{
					
				}
				
				LastDimensionMajorIterator operator++(int toIncrease)
				{
				
				}

				T &operator*() const
				{
					return nullptr;
				}


			};
	};
}

#endif
			
