#include <iostream>
#include <string>
#include <algorithm>

using std::cout;
using std::endl;

void printHeader() {
   cout << endl;
   cout << "================================================" << endl;
   cout << "No longer naive vector - an example taken from  "  << endl;
   cout << "         the lecture by Arthur O'Dwyer          " << endl;
   cout << "          RAII and the Rule of Zero             " << endl;
   cout << "                 CppCon 2019                    " << endl;
   cout << "================================================" << endl;
   cout << endl;
}

class Vec {

public:

   Vec() : ptr_( nullptr ), size_( 0 ) {}

   //A copy constructor to copy the resource (avoid double-frees)
   Vec( const Vec& rhs ) {
      ptr_ = new int[ rhs.size_ ];
      size_ = rhs.size_;
      std::copy( rhs.ptr_, rhs.ptr_ + size_, ptr_ );
   }

   //A move constructor, to transfer ownership of the resource (cheaper than copying)
   Vec( Vec && rhs ) noexcept {
      ptr_ = std::exchange( rhs.ptr_, nullptr );
      size_ = std::exchange( rhs.size_, 0 );
   }

   //A destructor to free the resource (avoid leaks)
   ~Vec() {
      delete [] ptr_;
   }

   //A member swap too, for simplicity
   void swap( Vec & rhs) noexcept {
      using std::swap;
      swap( ptr_, rhs.ptr_ );
      swap( size_, rhs.size_ );
   }

   //An assigment operator to free the left-hand resource and transfer ownership
   // of the right-hand one
   // ??? : Vec copy OR: Vec & copy
   Vec & operator= (Vec copy) {
      copy.swap( * this);
      return * this;
   }

   //A two-argument swap, to make your type efficiently "std::swappable"
   friend void swap( Vec & a, Vec & b) noexcept {
      a.swap( b );
   }

private:
   int * ptr_;
   size_t size_;
};

int main(int argc, char *argv[]) {
   printHeader();

   cout << endl;
   return 0;
}
