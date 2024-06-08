# seedstarter
SeedStarter is a project that I've worked on during my third year of studies at the Faculty of Information Technologies in Mostar. It was a result of combining two seminar papers from the 5th semester of my studies, specifically "Design and development of Internet of Things projects" by prof. Elmir Babović (Result being a seedling incubator) and "Human-computer interaction" by prof. Dušanka Bošković (Result being a .NET MAUI cross-platform application). With a little bit of aditional work I was able to complete the project and present it at the 2024 edition of our FIT Coding Challenge. I wasn't fortunate enough to make it into top three projects, but I'm glad that I've had the opportunity to present my work at such high level.

On the other hand, my colleagues from the team "Spinewise" were fenomenal during the whole competition and they secured the 1st place there. Feel free to check out theit project via the [link](https://github.com/ArminDjidelija/fitcc24-spinewise).

## Description
The SeedStarter project contains both software and hardware part that are needed to access all of the capabilities it provides. Both of these parts work together to help the user with monitoring and control of the four key parameters for plant development—temperature, soil humidity, air humidity and light. These parameters are a crucial aspect for proper plant development in their early stages and need to be monitored on a regular level. This monitoring is acomplished with 2 sensors contained in the incubator, while their control is acomblished by implementing 4 types of gadgets for their control.

## Functionalities

### Mobile App
Mobile app was built based on the designed made by my colleague [Ensar Čevra](https://github.com/EnsarCevra) and I while working on our seminar paper for "Human-computer interaction" subject. It follows some of the basic design patterns that are contained in the ["Designing Interfaces: Patterns for Effective Interaction Design"](https://www.amazon.com/Designing-Interfaces-Patterns-Effective-Interaction/dp/1492051969) by Jenifer Tidwell, Charles Brewer, Aynne Valencia. Mobile application is responsible for visually informing the user about the values of key parameters from inside the incubator, and it is also responsible for giving the user an option to turn on the gadgets responsible for parameter control inside the incubator.

<p align="center">
  <img src="https://github.com/zmehic/teachy-angular-asp.net/assets/60481114/df7aff81-5771-46b1-881a-166c4264e7f0" alt="Test management" width="235" height="540">
  <img src="https://github.com/zmehic/teachy-angular-asp.net/assets/60481114/67899634-43ee-4acb-b632-e7231171c70e" alt="Test management" width="235" height="540">
  <img src="https://github.com/zmehic/teachy-angular-asp.net/assets/60481114/60acff1d-6ab9-4a75-94b9-cc6237676e33" alt="Test management" width="235" height="540">
  <img src="https://github.com/zmehic/teachy-angular-asp.net/assets/60481114/cb27a377-37ad-4bc4-947c-d094082d8a75" alt="Test management" width="235" height="540">
</p>

The application itself contains four destinct pages:
- Home page - which contains all of the information and controlls the user needs to start using the system. This approach follows the "Direct Mobile Access" design pattern;
- Monitor - which is currently not implemented, should give livestream video from inside the incubator itself;
- Statistics - which gives the user an ability to search into past values of key parameters; (With detailed statistics for each parameter);
- Settings - which gives the user an ability to choose from three different operation modes and to insert the type of seedling they are trying to grow;

### Incubator
Incubator contains all of the necesarry sensors and gadgets needed to control and monitor these key parameters.

**Components:**
- DHT11 Sensor for Air Humidity and Temperature;
- Two 12v Fans;
- Ultrasonic Mist Maker;
- PTC Heater Element;
- 8 Channel Relay Board;
- NodeMcu ESP8266 ESP-12E;
- Led Grow Waterproof Light Strip;
- LM7805 Voltage Regulator;
- Soil Hygrometer Detection Module;

<p align="center">
  <img src="https://github.com/zmehic/teachy-angular-asp.net/assets/60481114/b6f5d8ad-cce8-4e95-94b3-87456302f521" alt="Test management" width="800" height="400">
</p>



## Conclusion
This project's aim is to make the lives of farmers and other peple who spend a lot of their time monitoring and controlling the environment for seedling production much easier.
