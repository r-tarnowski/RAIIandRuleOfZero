#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using std::cout;
using std::endl;

void printHeader() {
   cout << endl;
   cout << "================================================" << endl;
   cout << "  Rule of Zero Vector - an example taken from   " << endl;
   cout << "         the lecture by Arthur O'Dwyer          " << endl;
   cout << "          RAII and the Rule of Zero             " << endl;
   cout << "                 CppCon 2019                    " << endl;
   cout << "================================================" << endl;
   cout << endl;
}

class Vec {

public:

   Vec() = default;

   //A copy constructor to copy the resource (avoid double-frees)
   Vec( const Vec& rhs ) = default;

   //A move constructor, to transfer ownership of the resource (cheaper than copying)
   Vec( Vec && rhs ) noexcept = default;

   Vec & operator= ( const Vec & rhs ) noexcept = default;

   Vec & operator= ( Vec && rhs ) noexcept = default;

   //A destructor to free the resource (avoid leaks)
   ~Vec() = default;

   //A member swap ownership: now only for performance, not correctness
   void swap( Vec & rhs) noexcept {
      vec_.swap( rhs.vec_ );
   }

   void push_back( int newVal ) {
      vec_.push_back( newVal );
      cout << "push_back( " << newVal << " ) called" << endl;
   }

   int & operator[]( size_t pos ) {
      //cout << "operator[]( " << pos << " ) called" << endl;
      return vec_[ pos ];
   }

   //A two-argument swap, to make your type efficiently "std::swappable"
   friend void swap( Vec & a, Vec & b) noexcept {
      a.swap( b );
      cout << "Friend swap called" << endl;
   }

   friend std::ostream& operator<<(std::ostream& os, const Vec & vec) {
      os << "Size: " << vec.vec_.size();
      if ( vec.vec_.size() > 0 ) {
         os << ", element(s): ";
         for ( size_t i = 0; i < vec.vec_.size(); ++ i) {
            os << vec.vec_[ i ] << ( i == ( vec.vec_.size() - 1 ) ? "" : ", ");
         }
      }
      return os;
   }

private:
  std::vector<int> vec_;
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
   cout << "vec : " << vec << endl;
   cout << "vec3 : " << vec3 << endl;

   cout << "-------------------------------------------------------------------" << endl;
   cout << "vec : " << vec << endl;
   cout << "vec2 : " << vec2 << endl;
   cout << "vec2 = vec;" << endl;
   vec2 = vec;
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
