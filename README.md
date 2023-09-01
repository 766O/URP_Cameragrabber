# URP_Cameragrabber

### 데이터 취득을 위한 과정

MLOPS 과정에서 확인할 수 있듯이 문제를 정의하고 문제 해결 방법찾은후에 해당 문제를 인공지능으로 해결하기 위해서 문제해결에 필요한 데이터를 모으는 과정이 필요
비전 모델을 활용하기 위해서는 센서 또는 카메라를 통해 데이터에 해당하는 이미지들을 취득
![image](https://github.com/766O/URP_Cameragrabber/assets/121467486/4ed549cb-b55c-4cd8-ade2-04d17e07fe9f)

![image](https://github.com/766O/URP_Cameragrabber/assets/121467486/555ab4c6-a50f-4952-b1cb-740cc7c377c9)

위와 같은 총 4대의 multispectral 카메라를 통해 grabber 과정 진행

---
### Program Flow
![image](https://github.com/766O/URP_Cameragrabber/assets/121467486/8c8ca739-83de-4354-ae4c-79081e614e64)

- Gig E 지원 및 각종 이미지 처리 지원 하는 eBUS SDK 활용

![image](https://github.com/766O/URP_Cameragrabber/assets/121467486/074c7627-6ae9-4959-9c30-01b0555cc5d9)

IPengine 에 해당하는 카메라 객체와 컴퓨터에서 처리하기 위한 pvDevice 객체를 카메라의 mac주소와 ip주소를 이용해서 연결 

이때 rgb 카메라에 대한 객체와 thermal 카메라에 대한 객체를 만들어서 

동시에 멀티쓰레드 프로그래밍을 진행 

각 객체에 대해 연결에 성공하면 이미지 데이터를 수신하기 위한 stream 을 오픈하는 과정을 거친후

파이프라인을 만들고 파이프라인의 버퍼에 카메라에서 받은 이미지의 정보를 저장

이를 통해서 버퍼를 활용하여 이미지 처리 4가지 기능구현


---


### GUI Programming


카메라와 임베디드 컴퓨터 인 젯슨나노를  연결해서 카메라의 정보를 받아 이미지로 처리하는 gui 프로그램 작성

![image](https://github.com/766O/URP_Cameragrabber/assets/121467486/c890abe6-92e3-400f-b6c8-6cbbbe40d0d4)


총 4 가지 기능 구현

- 버튼을누를때마다 각각의 카메라에서 정보를 받아올지 아니면 정보를 받지않고 있을지 를 결정하는 기능인 rgb,thermal camera on/off 
- 버튼을 눌렀을때 rgb,thermal 이미지를 저장하는 캡쳐기능
- record 버튼을 눌렀을때 부터 다시 record 버튼을 누를때까지 초당 30 프레임의 이미지를 바이너리파일로 저장하는 record 버튼
- 버튼을 눌렀을시 record 통해 저장된 이진파일을 다시 이미지로 바꿔주는 decode 기능


---
### 소감 

하드웨어를 다루는 프로그램을 처음으로 작성해봄

처음 C++를 다뤄서 꽤나 고생했으면서 초기에는 전체적인 흐름이 이해가 가지 않아서 힘들었다

또한 초기에는 객체프로그래밍의 의미 또한 이해하지 못했었다

다만 직접 데이터 취득하는 과정을 경험했다는점은 긍정적인 부분

주어진 시간이 한정적이어서 기본적인 기능구현만 간신히 성공했으며 2대의 카메라에 대해서만 작동하는 코드 (RGB 1 ,Thermal 1)

좀 더 다양한 조건에서도 오류 발생없이 작동하는 코드 짜도록 노력해야겠다




  

  

