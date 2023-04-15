#include <iostream>
#include <string>
#include <algorithm>
#include <memory>

using std::cout;
using std::endl;

void printHeader() {
   cout << endl;
   cout << "================================================" << endl;
   cout << " Closer To Rule of Zero - an example taken from "  << endl;
   cout << "         the lecture by Arthur O'Dwyer          " << endl;
   cout << "          RAII and the Rule of Zero             " << endl;
   cout << "                 CppCon 2019                    " << endl;
   cout << "================================================" << endl;
   cout << endl;
}

class Vec {

public:

   Vec() : uniquePtr( nullptr ), size_( 0 ) {
      cout << "Constructor called" << endl;
   }

   //copy the resource
   Vec( const Vec& rhs ) {
      uniquePtr = std::make_unique<int[]>( rhs.size_ );
      size_ = rhs.size_;
      std::copy( rhs.uniquePtr.get(), rhs.uniquePtr.get() + size_ , uniquePtr.get() );
      cout << "Copy constructor called" << endl;
   }

   //transfer ownership
   Vec( Vec && rhs ) noexcept =default;

   //free the resource
   ~Vec() = default;

   //A member swap too, for simplicity
   void swap( Vec & rhs) noexcept {
      using std::swap;
      swap( uniquePtr, rhs.uniquePtr );
      swap( size_, rhs.size_ );
      cout << "Member swap called" << endl;
   }

   //An assigment operator to free the left-hand resource and transfer ownership
   // of the right-hand one
   // ??? : Vec copy OR: Vec & copy
   Vec & operator= (Vec copy) noexcept {
      copy.swap( * this);
      cout << "Assignment operator called" << endl;
      return * this;
   }

   void push_back( int newVal ) {
      auto newPtr = std::make_unique<int[]>( size_ + 1 );
      std::copy( uniquePtr.get(), uniquePtr.get() + size_, newPtr.get());
      newPtr[ size_ ] = newVal;
      size_ ++;
      uniquePtr.reset();
      uniquePtr = std::move( newPtr);
      cout << "push_back( " << newVal << " ) called" << endl;
   }

   int & operator[]( size_t pos ) {
      //cout << "operator[]( " << pos << " ) called" << endl;
      return uniquePtr[ pos ];
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
         for ( size_t i = 0; i < vec.size_; ++ i) {
            os << vec.uniquePtr[ i ] << ( i == ( vec.size_ - 1 ) ? "" : ", ");
         }
      }
      return os;
   }

private:
   std::unique_ptr<int[]> uniquePtr;
   size_t size_;
};

int main(int argc, char *argv[]) {
   printHeader();
   cout << "-------------------------------------------------------------------" << endl;
   cout << "Vec vec;" << endl;
   //cout << "cout << vec << endl;" << endl;
   Vec vec;
   cout << "vec : " << vec << endl;

   cout << "-------------------------------------------------------------------" << endl;
   cout << "vec.push_back( 1 );" << endl;
   //cout << "cout << vec << endl;" << endl;
   vec.push_back( 1 );
   cout << "vec : " << vec << endl;

   cout << "-------------------------------------------------------------------" << endl;
   cout << "vec.push_back( 2 );" << endl;
   //cout << "cout << vec << endl;" << endl;
   vec.push_back( 2 );
   cout << "vec : " << vec << endl;

   cout << "-------------------------------------------------------------------" << endl;
   cout << "vec[ 1 ] = 3;" << endl;
   vec[ 1 ] = 3;

   //cout << "-------------------------------------------------------------------" << endl;
   //cout << "cout << \"vec[ 1 ] = \" << vec[ 1 ] << endl;" << endl;
   cout << "vec[ 1 ] = " << vec[ 1 ] << endl;

   cout << "-------------------------------------------------------------------" << endl;
   cout << "vec : " << vec << endl;
   cout << "Vec vec1( vec );" << endl;
   Vec vec1( vec );
   cout << "vec1 : " << vec1 << endl;

   cout << "-------------------------------------------------------------------" << endl;
   cout << "Vec vec2 = vec;" << endl;
   Vec vec2 = vec;
   cout << "vec2 : " << vec2 << endl;

   cout << "-------------------------------------------------------------------" << endl;
   cout << "vec : " << vec << endl;
   cout << "Vec vec3( std::move( vec ) );" << endl;
   Vec vec3( std::move( vec ) );
   cout << "ATTENTION: after std::move( vec ) vec is no longer valid! You can't print it!"<< endl;
   cout << "vec3 : " << vec3 << endl;

   cout << "-------------------------------------------------------------------" << endl;
   //cout << "vec : " << vec << endl;
   cout << "vec2 : " << vec2 << endl;
   cout << "vec = vec2;" << endl;
   vec = vec2;
   cout << "ATTENTION: after vec = vec2 vec is valid again! Now you can print it!"<< endl;
   cout << "vec : " << vec << endl;
   cout << "vec2 : " << vec2 << endl;

   cout << "-------------------------------------------------------------------" << endl;
   cout << "vec1[ 0 ] = 5;" << endl;
   vec1[ 0 ] = 5;
   cout << "vec1 : " << vec1 << endl;
   cout << "vec3 : " << vec3 << endl;
   cout << "std::swap( vec1, vec3 );" << endl;
   std::swap( vec1, vec3 );
   cout << "vec1 : " << vec1 << endl;
   cout << "vec3 : " << vec3 << endl;

   cout << "-------------------------------------------------------------------" << endl;
   cout << "vec1 : " << vec1 << endl;
   cout << "vec3 : " << vec3 << endl;
   cout << "swap( vec1, vec3 );" << endl;
   swap( vec1, vec3 );
   cout << "vec1 : " << vec1 << endl;
   cout << "vec3 : " << vec3 << endl;

   cout << "-------------------------------------------------------------------" << endl;


   cout << endl << "main() completed" << endl << endl;
   return 0;
}
