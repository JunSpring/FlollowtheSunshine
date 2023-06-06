import discord
import datetime
import pytz
import asyncio
import serial
import time

# 시리얼 포트와 통신 속도 설정
ser = serial.Serial('COM6', 9600)  # 시리얼 포트와 통신 속도를 맞게 설정해야 합니다.


async def schedule_commands():
    print("10minute alert")

    while True:
        current_minute = datetime.datetime.now().minute

        if current_minute % 10 == 0:
            ser.write('a'.encode())

            received = False
            while not received:
                start_time = time.time()
                while ser.in_waiting == 0:
                    if time.time() - start_time > 5:
                        print("No response within 5 seconds.")
                        break

                if ser.in_waiting > 0:
                    received_data = ser.readline().decode().rstrip()
                    received = True
                    print("Received data:", received_data)
                    break

            if received_data == 'sm':
                waterHistories.append(datetime.datetime.now())

        # 1분마다 체크
        await asyncio.sleep(60)


intents = discord.Intents.all()
client = discord.Client(intents=intents)

dev = "마이크로프로세서 프로젝트"

user_data = None
data_type = None
waterHistories = []


@client.event
async def on_ready():
    print(f'We have logged in as {client.user}')


@client.event
async def on_message(message):
    # 봇이 메시지를 보낸 경우 무시
    if message.author.bot:
        return

    # 사용자 입력 처리
    global user_data, data_type

    if message.content == '화분아 도움말':
        print("도움말 요청 명령어 입력")

        embed = discord.Embed(
            description=f'>>> **명령어 모음집**', timestamp=datetime.datetime.now(pytz.timezone('UTC')), colour=0x8ACA5C)
        embed.add_field(name="화분아 도움말", value=f"``화분이의 명령어를 알려줍니다.``", inline=False)
        embed.add_field(name="화분아 설정 이동거리(m)", value=f"``화분이 이동할 거리를 설정합니다.``",
                        inline=False)
        embed.add_field(name="화분아 알림", value=f"``화분의 정보 및 기록을 알려줍니다.``", inline=False)
        embed.add_field(name="화분아 정보", value=f"``화분이의 정보들을 알려 줍니다.``", inline=False)
        embed.set_author(name=f"{message.author.name} 님의 도움말", icon_url=message.author.avatar)
        embed.set_footer(text=dev)
        await message.reply(embed=embed, mention_author=True)

        print("도움말 데이터 전송완료!\n")

    if message.content == '화분아 정보':
        print("정보 요청 명령어 입력")

        embed = discord.Embed(description=f'', timestamp=datetime.datetime.now(pytz.timezone('UTC')), colour=0x8ACA5C)
        embed.set_author(name=f"{message.author.name} 님의 정보요청", icon_url=message.author.avatar)
        embed.add_field(name="핑", value=f">>> {int((client.latency * 1000))}ms", inline=False)
        embed.add_field(name="제작 기간", value=f">>> 2023-05-23 ~ 2023-06-07", inline=False)
        embed.set_footer(text=dev)
        await message.reply(embed=embed, mention_author=True)

        print("정보 데이터 전송완료!\n")

    if message.content == '화분아 센서정보':
        print("센서정보 요청 명령어 입력")

        ser.write('i'.encode())

        received = True
        while ser.in_waiting > 0:
            received_data = ser.readline().decode().rstrip()
            print("Received data:", received_data)
            ser.write(0)

        if received:
            received_data = received_data.split()
            soilMoisture = int(received_data[0])
            CDS1 = int(received_data[1])
            CDS2 = int(received_data[2])

            embed = discord.Embed(description=f'', timestamp=datetime.datetime.now(pytz.timezone('UTC')),
                                  colour=0x8ACA5C)
            embed.set_author(name=f"{message.author.name} 님의 센서정보 요청", icon_url=message.author.avatar)
            embed.add_field(name="토양수분센서", value=f">>> {soilMoisture}", inline=False)
            embed.add_field(name="광센서1", value=f">>> {CDS1}", inline=False)
            embed.add_field(name="광센서2", value=f">>> {CDS2}", inline=False)
            embed.set_footer(text=dev)

            print("센서 데이터 전송완료!\n")
        else:
            embed = discord.Embed(description=f"센서와 통신할 수 없습니다.",
                                  timestamp=datetime.datetime.now(pytz.timezone('UTC')), colour=0x8ACA5C)
            embed.set_author(name=f"{message.author.name} 님의 센서정보 요청", icon_url=message.author.avatar)
            embed.set_footer(text=dev)

            print("센서 데이터 전송실패...\n")
        await message.reply(embed=embed, mention_author=True)

    if message.content == '화분아 수분내역':
        print("수분내역 요청 명령어 입력")

        global waterHistories

        embed = discord.Embed(description=f'', timestamp=datetime.datetime.now(pytz.timezone('UTC')),
                              colour=0x8ACA5C)
        embed.set_author(name=f"{message.author.name} 님의 수분내역 요청", icon_url=message.author.avatar)

        for i, waterHistory in enumerate(waterHistories[-min(5, len(waterHistories)):]):
            embed.add_field(name=f"내역{i + 1}", value=f">>> {waterHistory}", inline=False)
            if i == 4:
                break
        embed.set_footer(text=dev)
        await message.reply(embed=embed, mention_author=True)

        print("수분내역 데이터 전송완료!\n")


# 봇 실행
client.run('MTExMDQ3OTY3MDI2NjMwNjY2MA.GkMawd.gUBI6n3Msgl3bbKP8L1EaIwD4jJZlKeVzZZ8QM')
# asyncio.run(schedule_commands())
