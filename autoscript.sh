cmake -S . -B build && cmake --build build && ./build/Demo_App #dong lenh cmake -S . -B build se tao ra folder build
#Cmake --build build se File thuc thi tuc la kieu dong lenh cd vao folder build r su dung lenh cmake
#con lenh cuoi cung la thuc thi file Demo_App
cmake --install build --prefix output_package
