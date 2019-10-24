#pragma once

class HomeLine {
public:
  HomeLine();
  void publishData();
private:
  WebSocketsClient webSocketClient;
};
