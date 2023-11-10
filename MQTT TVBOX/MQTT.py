import paho.mqtt.client as mqtt
from random import uniform
import time

mqttBroker = "test.mosquitto.org"
client = mqtt.Client("TEMPERATURA")
client.connect(mqttBroker,1883)


while True:
    aleatorio = uniform(20.0, 21.0)
    client.publish("TEMPERATURA", aleatorio)
    print("Confirmada a publicação " + str(aleatorio) + " para o tópico")

    time.sleep(10)