### iterator
iterator(반복자)는 모든 반복 가능한 stl컨테이너에 사용 가능하다.  
처음(begin)과 끝(end)가 정해져 있는 컨테이너에서 반복문(범위기반 for)을 이용할 때 주로 사용  
컨테이너 내부에서 인덱스를 이동할 수 있다.  
일반적인 iterator의 경우, index[0]부터 end까지 이동한다.  
reverse_iterator사용시, end->start로 접근한다.  
연속/연결된 객체에 대한 반복자 선언
```cpp
vector<int> v;
vector<int>::iterator iter = v.begin();
```
  
연속된 자료 구조에서는 주소값이 +되는 형태  
  

## 연속된 자료 구조
연속된 자료 구조는 자료 구조 내의 데이터의 저장 위치(주소)가 모두 연결되어 있는 구조를 말한다  
ex) `arr[0]`의 주소:`1x20`, `arr[1]`의 주소:`1x24`  
  
### std::array
메모리를 자동으로 할당하고 헤제 (데이터를 힙에 저장)  
indexoutofrange 예외를 검사해주는 원소 접근 메서드 at()  
operator[]를 통해 c스타일 배열과 같이 index에 접근이 가능하다  
index의 주소를 가리키는 iterator관련 함수가 정의되어 있다  
```cpp
array<int, 3> arr;

array<int, 3>::iterator iter = arr.begin();
cout << *iter << '\t';
iter += 2;
cout << *iter << '\n';

int* it = arr.data();
cout << it << '\t';
it++;
cout << it;
```
출력 결과
```cmd
-858993460      -858993460
000000B29C6FF998        000000B29C6FF99C
```
출력 결과에서 -(num)의 경우 아무 숫자도 들어가 있지 않이 때문에 있는 쓰레기 값  
16진수->arr이 들어있는 주소  
begin(). end()와 같은 경우 참조자를 반환, data()의 경우 컨테이너의 시작 지점 주소를 반환  
  
operator+를 이용, 배열을 이어 합칠 수 있다  
  
  
### std::vector

std::array의 상향된 버전
- 크기 변경 가능
- 원소의 추가, 삭제 가능
- 힙 메모리 사용

동작 방식
1. 선언시 용량을 할당한다.
2. 원소 추가시 용량이 남아 있다면 그대로 추가, 시간복잡도 O(1).
3. 원소 추가시 용량이 남아 있지 않다면 모든 원소를 복사, 이동.  이때 시간복잡도는 O(n), n의 크기는 추가한 원소의 개수.
4. O(n)의 시간복잡도 발생의 방지를 위해, 일반적으로 용량이 부족할 때마다 두 배로 용량을 증가.  (중간에 원소 삽입은 항상 O(n))

## 연결된 자료 구조

### list
데이터 중간에 자료를 추가하거나 삭제하는 작업에서의 효율이 높다.  

#### std::forward_list
원소의 삽입과 삭제가 노드의 포인터 조작으로 구현된다  
forward_list의 경우, 다음 노드를 가리키는 next포인터만을 포함한다.  
따라서 원소의 삽입과 삭제시 배열과 같이 원소의 저장 위치를 밀 필요가 없고, 원소의 삽입/삭제의 시간복잡도가 O(n)으로 고정된다.  
객체에서 const멤버변수를 이용해 first node의 주소를 저장해둔다.  
push_front()함수의 사용으로 first node가 바뀌어야 할 때, 새로 추가된 node의 next포인터는 원래 척 노드의 주소를 가리키고, first node의 주소가 저장된 const멤버 변수가 새로운 first node의 주소를 저장하게 된다.  
