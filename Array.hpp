#ifndef ASSIGNMENT4_ARRAY_HPP
#define ASSIGNMENT4_ARRAY_HPP

#include <exception>
#include <cstdio>

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
			Array() : array(new Array<T, Dims...>)
			{
			    arraySize = 0;
		        for(auto value: array)
                {
		            arraySize++;
                }
                static_assert(arraySize > 0);
			}

			//Copy Constructor
			Array(const Array &toCopy)
			{
                if(arraySize != toCopy.arraySize)
                {
                    printf("Error, mismatch in array size.\n");
                    return;
                }
				for(std::size_t i = 0; i < arraySize; i++)
                {
				    array[i] = toCopy[i];
                }
			}

			//Copy Consturctor (Templated)
			template <typename U>
			Array(const Array<U, Dims...> &toCopyTemplated)
			{
					
			}

			//Assignment Operator
			Array& operator=(const Array &assignment)
			{
				if(this != &assignment)
                {
				    if(arraySize != assignment.arraySize)
                    {
				        throw OutOfRange();
                    }
				    for(std::size_t i = 0; i < arraySize; i++)
                    {
				        array[i] = assignment[i];
                    }
                }
				return *this;
			}

			//Assignment Operator (Templated)
			template <typename U>
			Array& operator=(const Array<U, Dims...> &assignment)
			{
			    if(this != assignment) {
                    if (arraySize != assignment.arraySize) {
                        throw OutOfRange();
                    }
                    for (std::size_t i = 0; i < arraySize; i++) {
                        array[i] = assignment[i];
                    }
                }
                return *this;
			}

			T &operator[](std::size_t i)
			{
			    if(i >= arraySize)
                {
			        throw OutOfRange();
                }
				return array[i];
			}
			
			const T &operator[](std::size_t i) const
			{
			    if(i >= arraySize)
                {
			        throw OutOfRange();
                }
				return array[i];
			}


			//Iterators

			FirstDimensionMajorIterator fmbegin()
			{
                FirstDimensionMajorIterator it;
                it.arrays = this;
                it.isEndIndex = false;
                it.lowOrderIterator = array[0].fmbegin();
                return it;
			}

			FirstDimensionMajorIterator fmend()
			{
		        FirstDimensionMajorIterator it;
		        it.arrays = this;
		        it.isEndIndex = true;
		        it.lowOrderIterator = array[0].fmend();
		        return it;
			}

			LastDimensionMajorIterator lmbegin()
			{
                LastDimensionMajorIterator it;
                it.arrays = this;
                it.isEndIndex = false;
                it.lowOrderIterator = array[0].lmbegin();
                return it;
			}

			LastDimensionMajorIterator lmend()
			{
			    LastDimensionMajorIterator it;
			    it.arrays = this;
			    it.isEndIndex = true;
			    it.lowOrderIterator = array[0].lmend();
			    return it;

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
			        currentIndex = 0;
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
				
				LastDimensionMajorIterator &operator=(const LastDimensionMajorIterator &toAssign)
				{
				    return nullptr;
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
			
