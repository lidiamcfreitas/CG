#!/bin/bash
obj=$(<$1)
vertices=($(echo "$obj" | grep "^v " | cut -c 3- | xargs printf '%f '))
normals=($(echo "$obj" | grep "^vn " | cut -c 4- | xargs printf '%f '))
uvs=($(echo "$obj" | grep "^vt " | cut -c 3- | xargs printf '%f '))
faces=($(echo "$obj" | grep "^f" | cut -c 3- | tr '/' ' ' | xargs -n 1 expr -1 +))
buffer=()
for (( i = 0 ; i < ${#faces[@]}; i+=3 )) do
vi=$((${faces[$(($i+0))]}*3))
ui=$((${faces[$(($i+1))]}*2))
ni=$((${faces[$(($i+2))]}*3))
buffer+=("${vertices[$(($vi+0))]}")
buffer+=("${vertices[$(($vi+1))]}")
buffer+=("${vertices[$(($vi+2))]}")
buffer+=("${normals[$(($ni+0))]}")
buffer+=("${normals[$(($ni+1))]}")
buffer+=("${normals[$(($ni+2))]}")
buffer+=("${uvs[$(($ui+0))]}")
buffer+=("${uvs[$(($ui+1))]}")
done
vertexFormat=$(printf "%s," "${buffer[@]}")
vertexFormat=${vertexFormat%?}
main="#import <Foundation/Foundation.h>
static float buffer[] = { $vertexFormat };
int main(int argc, const char* argv[]) {
NSData* data = [NSData dataWithBytes:&buffer length:sizeof(buffer)];
[data writeToFile:@\"$2.mbo\" atomically:YES];
return 0;
}"
echo "${main}" > main.m
clang -fobjc-arc main.m -o main_app
./main_app
rm main.m main_app
echo now add the file to xcode