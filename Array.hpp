#ifndef MARVIN_ARRAY_HPP
#define MARVIN_ARRAY_HPP

#include <exception>

namespace cs540 {
  struct OutOfRange: public std::exception {
    const char * what() const
    throw () {
      return "ERROR: Array Out Of Range";
    }
  };

  template < typename T, std::size_t dimensions, std::size_t...Dims >
    class Array {
      static_assert(dimensions > 0);

      public:
        std::size_t arraySize;
      Array < T, Dims... > * array;
      static T ValueType;

      //Default Constructor
      Array(): arraySize(dimensions), array(new Array < T, Dims... > [arraySize]) {}

      //Copy Contructor
      Array(const Array & toCopy): arraySize(toCopy.arraySize), array(new Array < T, Dims... > [arraySize]) {
        for (std::size_t i = 0; i < arraySize; i++) {
          array[i] = toCopy.array[i];
        }
      }

      //Copy Constructor (Templated)
      template < typename U >
        Array(const Array < U, dimensions, Dims... > & toCopy): arraySize(toCopy.arraySize), array(new Array < T, Dims... > [arraySize]) {
          for (std::size_t i = 0; i < arraySize; i++) {
            array[i] = toCopy.array[i];
          }
        }

        //Destructor (not required but figured it'd help)
        ~Array() {
          delete[] array;
        }

      //Assignment Operator 
      Array & operator = (const Array & toAssign) {
        if (this != & toAssign) {
          if (arraySize != toAssign.arraySize) {
            throw OutOfRange();
          }

          for (std::size_t i = 0; i < arraySize; i++) {
            array[i] = toAssign.array[i];
          }
        }

        return *this;
      }

      //Assignment Operator (Templated)
      template < typename U >
        Array & operator = (const Array < U, dimensions, Dims... > & toAssign) {
          if (arraySize != toAssign.arraySize) {
            throw OutOfRange();
          }

          for (std::size_t i = 0; i < arraySize; i++) {
            array[i] = toAssign.array[i];
          }

          return *this;
        }

      //Index Operator
      Array < T, Dims... > & operator[](const std::size_t i) {
        if (i >= arraySize) {
          throw OutOfRange();
        }

        return array[i];
      }

      //Index Operator for const
      const Array < T, Dims... > & operator[](const std::size_t i) const {
        if (i >= arraySize) {
          throw OutOfRange();
        }

        return array[i];
      }

      class FirstDimensionMajorIterator {
        public:
          std::size_t arraySize, currentIndex;
        bool isEndIndex;
        Array < T, dimensions, Dims... > * array;
        typename Array < T, Dims... > ::FirstDimensionMajorIterator lowOrderIterator;

        public:
          //Default constructor
          FirstDimensionMajorIterator():
          arraySize(dimensions), currentIndex(0),
          isEndIndex(false), array(nullptr) {}

        //Copy Constructor
        FirstDimensionMajorIterator(const FirstDimensionMajorIterator & toCopy) =
          default;

        //Assignment Operator
        FirstDimensionMajorIterator & operator = (const FirstDimensionMajorIterator & toAssign) =
          default;

        //Equals Operator
        bool operator == (const FirstDimensionMajorIterator & other) {
          // All values must match or it will return false
          // Otherwise, see if it's at the end
          // If it's not at the end, go a layer deeper
          if (
            (arraySize != other.arraySize) ||
            (currentIndex != other.currentIndex) ||
            (isEndIndex != other.isEndIndex) ||
            (array != other.array)
          ) {
            return false;
          } else if (isEndIndex) {
            return true;
          } else {
            // Recursive call to next layer
            return lowOrderIterator == other.lowOrderIterator;
          }
        }

        //Not Equal Operator
        bool operator != (const FirstDimensionMajorIterator & other) {
          return !(operator == (other));
        }

        //Incrementer
        FirstDimensionMajorIterator & operator++() {
          lowOrderIterator++;
          if (lowOrderIterator.isEndIndex && lowOrderIterator.currentIndex == 0) {
            if (++currentIndex == arraySize) {
              currentIndex = 0;
              isEndIndex = true;
            } else {
              isEndIndex = false;
            }

            // Go to the next layer down
            lowerDimension();
          }

          return *this;
        }

        //Incrementer
        FirstDimensionMajorIterator operator++(int) {
          auto temp = * this;
          ++( * this); // Call operator++()
          return temp;
        }

        //Returns reference to the T
        T & operator * () const {
          return *lowOrderIterator;
        }

        //Helper function
        void lowerDimension() {
          lowOrderIterator.array = & (array -> array[currentIndex]);
          lowOrderIterator.isEndIndex = false;
          lowOrderIterator.lowerDimension();
        }
      };

      class LastDimensionMajorIterator {
        public:
          std::size_t arraySize, currentIndex;
        bool isEndIndex;
        Array < T, dimensions, Dims... > * array;
        typename Array < T, Dims... > ::LastDimensionMajorIterator lowOrderIterator;

        public:
          //Default Constructor
          LastDimensionMajorIterator():
          arraySize(dimensions), currentIndex(0),
          isEndIndex(false), array(nullptr) {}

        //Copy Constructor
        LastDimensionMajorIterator(const LastDimensionMajorIterator & toCopy) =
          default;

        //Assignment Operator
        LastDimensionMajorIterator & operator = (const LastDimensionMajorIterator & toAssign) =
          default;

        //Equals Operator
        bool operator == (const LastDimensionMajorIterator & other) {
          // All values must match or it will return false
          // Otherwise, see if it's at the end
          // If it's not at the end, go a layer deeper
          if (
            (arraySize != other.arraySize) ||
            (currentIndex != other.currentIndex) ||
            (isEndIndex != other.isEndIndex) ||
            (array != other.array)
          ) {
            return false;
          } else if (isEndIndex) {
            return true;
          } else {
            // Compare the next layer down
            return lowOrderIterator == other.lowOrderIterator;
          }
        }

        //Not Equal Operator
        bool operator != (const LastDimensionMajorIterator & other) {
          return !(operator == (other));
        }

        //Incrementer
        LastDimensionMajorIterator & operator++() {
          currentIndex = (currentIndex + 1) % arraySize;
          if (currentIndex == 0) {
            isEndIndex = true;
            lowOrderIterator++;
          }
          lowerDimension();

          return *this;
        }

        //Incrementer
        LastDimensionMajorIterator operator++(int) {
          auto temp = * this;
          ++( * this);
          return temp;
        }

        //Returns reference to the T
        T & operator * () const {
          return *lowOrderIterator;
        }

        //Helper function
        void lowerDimension() {
          lowOrderIterator.array = & (array -> array[currentIndex]);
          lowOrderIterator.lowerDimension();
          isEndIndex = lowOrderIterator.isEndIndex;
        }
      };

      FirstDimensionMajorIterator fmbegin() {
        FirstDimensionMajorIterator it;
        it.array = this;
        it.isEndIndex = false;
        it.lowOrderIterator = array[0].fmbegin();
        return it;
      }

      FirstDimensionMajorIterator fmend() {
        FirstDimensionMajorIterator it;
        it.array = this;
        it.isEndIndex = true;
        it.lowOrderIterator = array[0].fmend();
        return it;
      }

      LastDimensionMajorIterator lmbegin() {
        LastDimensionMajorIterator it;
        it.array = this;
        it.isEndIndex = false;
        it.lowOrderIterator = array[0].lmbegin();
        return it;
      }

      LastDimensionMajorIterator lmend() {
        LastDimensionMajorIterator it;
        it.array = this;
        it.isEndIndex = true;
        it.lowOrderIterator = array[0].lmend();
        return it;
      }
    };

  // Base Class
  template < typename T, std::size_t dimensions >
    class Array < T, dimensions > {
      static_assert(dimensions > 0);

      public: std::size_t arraySize;
      T * array;
      static T ValueType;
      class FirstDimensionMajorIterator;
      class LastDimensionMajorIterator;

      //Default Constructor
      Array(): arraySize(dimensions),
      array(new T[arraySize]) {}

      //Copy Contructor
      Array(const Array & toCopy): arraySize(toCopy.arraySize),
      array(new T[arraySize]) {
        for (std::size_t i = 0; i < arraySize; i++) {
          array[i] = toCopy.array[i];
        }
      }

      //Copy Constructor (Templated)
      template < typename U >
      Array(const Array < U, dimensions > & toCopy): arraySize(toCopy.arraySize),
      array(new T[arraySize]) {
        for (std::size_t i = 0; i < arraySize; i++) {
          array[i] = toCopy.array[i];
        }
      }

      //Destructor (not required but figured it'd help)
      ~Array() {
        delete[] array;
      }

      //Equals Operator
      Array & operator = (const Array & toAssign) {
        if (this != & toAssign) {
          arraySize = toAssign.arraySize;

          for (std::size_t i = 0; i < arraySize; i++) {
            array[i] = toAssign.array[i];
          }
        }

        return *this;
      }

      //Equals Operator (Templated)
      template < typename U >
      Array & operator = (const Array < U, dimensions > & toAssign) {
        arraySize = toAssign.arraySize;

        for (std::size_t i = 0; i < arraySize; i++) {
          array[i] = toAssign.array[i];
        }

        return *this;
      }

      //Index Operator
      T & operator[](const std::size_t i) {
        if (i >= arraySize) {
          throw OutOfRange();
        }

        return array[i];
      }

      //Index Operator for const
      const T & operator[](const std::size_t i) const {
        if (i >= arraySize) {
          throw OutOfRange();
        }

        return array[i];
      }

      class FirstDimensionMajorIterator {
        public:
          std::size_t arraySize, currentIndex;
        bool isEndIndex;
        Array < T, dimensions > * array;
        T * data;

        public:
          //Default Constructor
          FirstDimensionMajorIterator():
          arraySize(dimensions), currentIndex(0),
          isEndIndex(false), array(nullptr),
          data(nullptr) {

          }

        //Copy Constructor
        FirstDimensionMajorIterator(const FirstDimensionMajorIterator & toCopy) =
          default;

        //Assignment Operator
        FirstDimensionMajorIterator & operator = (const FirstDimensionMajorIterator & toAssign) =
          default;

        //Equals Operator
        bool operator == (const FirstDimensionMajorIterator & other) {
          // All values must match or it will return false
          // Otherwise, see if it's at the end
          // If it's not at the end, go a layer deeper
          if (
            (arraySize != other.arraySize) ||
            (currentIndex != other.currentIndex) ||
            (isEndIndex != other.isEndIndex) ||
            (array != other.array) ||
            (data != other.data)
          ) {
            return false;
          } else if (isEndIndex) {
            return true;
          } else {
            return data == other.data;
          }
        }

        //Not Equals Operator
        bool operator != (const FirstDimensionMajorIterator & other) {
          return !(operator == (other));
        }

        //Incrementer
        FirstDimensionMajorIterator & operator++() {
          if (++currentIndex == arraySize) {
            currentIndex = 0;
            isEndIndex = true;
          } else {
            isEndIndex = false;
          }

          lowerDimension();

          return *this;
        }

        //Incrementer
        FirstDimensionMajorIterator operator++(int) {
          auto temp = * this;
          ++( * this);
          return temp;
        }

        //Returns reference to the T
        T & operator * () const {
          return *data;
        }

        //Helper function
        void lowerDimension() {
          data = & (array -> array[currentIndex]);
        }
      };

      class LastDimensionMajorIterator {
        public:
          std::size_t arraySize, currentIndex;
        bool isEndIndex;
        Array < T, dimensions > * array;
        T * data;

        public:
          //Default Constructor
          LastDimensionMajorIterator():
          arraySize(dimensions), currentIndex(0),
          isEndIndex(false), array(nullptr),
          data(nullptr) {}

        //Copy Constructor
        LastDimensionMajorIterator(const LastDimensionMajorIterator & toCopy) =
          default;

        //Assignment Operator
        LastDimensionMajorIterator & operator = (const LastDimensionMajorIterator & toAssign) =
          default;

        //Equals Operator
        bool operator == (const LastDimensionMajorIterator & other) {
          if (
            (arraySize != other.arraySize) ||
            (currentIndex != other.currentIndex) ||
            (isEndIndex != other.isEndIndex) ||
            (data != other.data)
          ) {
            return false;
          } else if (isEndIndex) {
            return true;
          } else {
            return data == other.data;
          }
        }

        //Not Equals Operator
        bool operator != (const LastDimensionMajorIterator & other) {
          return !(operator == (other));
        }

        //Incrementer
        LastDimensionMajorIterator & operator++() {
          if (++currentIndex == arraySize) {
            currentIndex = currentIndex % arraySize;
            isEndIndex = true;
          } else {
            isEndIndex = false;
          }

          lowerDimension();
          return *this;
        }

        //Incrementer
        LastDimensionMajorIterator operator++(int) {
          auto temp = * this;
          ++( * this);
          return temp;
        }

        //Returns reference to the T
        T & operator * () const {
          return *data;
        }

        //Helper function
        void lowerDimension() {
          data = & (array -> array[currentIndex]);
        }
      };

      FirstDimensionMajorIterator fmbegin() {
        FirstDimensionMajorIterator it;
        it.array = this;
        it.data = & (array[0]);
        it.isEndIndex = false;
        return it;
      }

      FirstDimensionMajorIterator fmend() {
        FirstDimensionMajorIterator it;
        it.array = this;
        it.data = & (array[0]);
        it.isEndIndex = true;
        return it;
      }

      LastDimensionMajorIterator lmbegin() {
        LastDimensionMajorIterator it;
        it.array = this;
        it.data = & (array[0]);
        it.isEndIndex = false;
        return it;
      }

      LastDimensionMajorIterator lmend() {
        LastDimensionMajorIterator it;
        it.array = this;
        it.data = & (array[0]);
        it.isEndIndex = true;
        return it;
      }
    };
}

#endif //MARVIN_ARRAY_HPP
