import paho.mqtt.client as mqtt
from random import uniform
import time

#IP rede notebook: 192.168.137.176
#IP rede LEHSA: 10.0.0.154

mqttBroker = "10.0.0.154"
client = mqtt.Client("TEMPERATURA")
client.connect(mqttBroker,1883)


while True:
    aleatorio = uniform(20.0, 21.0)
    client.publish("TEMPERATURA", aleatorio)
    print("Confirmada a publicação " + str(aleatorio) + " para o tópico")

    time.sleep(10)
