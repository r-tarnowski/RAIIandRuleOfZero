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

   Vec() : ptr_( nullptr ), size_( 0 ) {
      cout << "Constructor called" << endl;
   }

   //A copy constructor to copy the resource (avoid double-frees)
   Vec( const Vec& rhs ) {
      ptr_ = new int[ rhs.size_ ];
      size_ = rhs.size_;
      std::copy( rhs.ptr_, rhs.ptr_ + size_, ptr_ );
      cout << "Copy constructor called" << endl;
   }

   //A move constructor, to transfer ownership of the resource (cheaper than copying)
   Vec( Vec && rhs ) noexcept {
      ptr_ = std::exchange( rhs.ptr_, nullptr );
      size_ = std::exchange( rhs.size_, 0 );
      cout << "Move constructor called" << endl;
   }

   //A destructor to free the resource (avoid leaks)
   ~Vec() {
      delete [] ptr_;
      cout << "Destructor called" << endl;
   }

   //A member swap too, for simplicity
   void swap( Vec & rhs) noexcept {
      using std::swap;
      swap( ptr_, rhs.ptr_ );
      swap( size_, rhs.size_ );
      cout << "Member swap called" << endl;
   }

   //An assigment operator to free the left-hand resource and transfer ownership
   // of the right-hand one
   // ??? : Vec copy OR: Vec & copy
   Vec & operator= (Vec copy) {
      copy.swap( * this);
      cout << "Assignment operator called" << endl;
      return * this;
   }

   void push_back( int newVal ) {
      int * newPtr = new int[ size_ + 1 ];
      std::copy( ptr_, ptr_ + size_, newPtr );
      delete[] ptr_;
      ptr_ = newPtr;
      ptr_[size_] = newVal;
      size_ ++;
      cout << "push_back( " << newVal << " ) called" << endl;
   }

   //A two-argument swap, to make your type efficiently "std::swappable"
   friend void swap( Vec & a, Vec & b) noexcept {
      a.swap( b );
      cout << "Friend swap called" << endl;
   }

   friend std::ostream& operator<<(std::ostream& os, const Vec & vec) {
      os << "Size: " << vec.size_;
      if ( vec.size_ > 0 ) {
         os << ", element(s): ";
         for ( int i = 0; i < vec.size_; ++ i) {
            os << vec.ptr_[ i ] << ( i == ( vec.size_ - 1 ) ? "" : ", ");
         }
      }
      return os;
   }

private:
   int * ptr_;
   size_t size_;
};

int main(int argc, char *argv[]) {
   printHeader();
   cout << "-------------------------------------------------------------------" << endl;
   cout << "Vec vec;" << endl;
   cout << "cout << vec << endl;" << endl;
   Vec vec;
   cout << vec << endl;

   cout << "-------------------------------------------------------------------" << endl;
   cout << "vec.push_back( 1 );" << endl;
   cout << "cout << vec << endl;" << endl;
   vec.push_back( 1 );
   cout << vec << endl;

   cout << "-------------------------------------------------------------------" << endl;
   cout << "vec.push_back( 2 );" << endl;
   cout << "cout << vec << endl;" << endl;
   vec.push_back( 2 );
   cout << vec << endl;

   cout << "-------------------------------------------------------------------" << endl;
   cout << "Vec vec1( vec );" << endl;
   Vec vec1( vec );

   cout << "-------------------------------------------------------------------" << endl;
   cout << "Vec vec2 = vec;" << endl;
   Vec vec2 = vec;

   cout << "-------------------------------------------------------------------" << endl;
   cout << "Vec vec3( std::move( vec ) );" << endl;
   Vec vec3( std::move( vec ) );

   cout << "-------------------------------------------------------------------" << endl;
   cout << "vec2 = vec;" << endl;
   vec2 = vec;

   cout << "-------------------------------------------------------------------" << endl;
   cout << "std::swap( vec1, vec3 );" << endl;
   std::swap( vec1, vec3 );

   cout << "-------------------------------------------------------------------" << endl;
   cout << "swap( vec1, vec3 );" << endl;
   swap( vec1, vec3 );

   cout << "-------------------------------------------------------------------" << endl;


   cout << endl << "main() completed" << endl << endl;
   return 0;
}
