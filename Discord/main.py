import discord
import datetime
import pytz
import asyncio
import serial

# 시리얼 포트와 통신 속도 설정
ser = serial.Serial('COM5', 9600)  # 시리얼 포트와 통신 속도를 맞게 설정해야 합니다.

intents = discord.Intents.all()
client = discord.Client(intents=intents)

dev = "마이크로프로세서 프로젝트"

user_data = None
data_type = None
waterHistories = []


@client.event
async def on_ready():
    print(f'We have logged in as {client.user}')
    print()

    global waterHistories

    while True:
        current_minute = datetime.datetime.now().minute

        received_data = None
        if current_minute % 10 == 0:
            print("10분마다 보드알림")

            while not(received_data == 'sm' or received_data == 'none'):
                ser.write('a'.encode())
                while ser.in_waiting > 0:
                    received_data = ser.readline().decode().rstrip()
                    ser.write(0)
            print("10분마다 보드알림 전송완료!")

            if received_data == 'sm':
                waterHistories.append(datetime.datetime.now())
                print("급수내역 업데이트 완료!")

            print()

        # 1분마다 체크
        await asyncio.sleep(60)


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

        received_data = ""
        while not(len(received_data.split()) == 3 and all(data.isdigit() for data in received_data.split())):
            ser.write('i'.encode())
            while ser.in_waiting > 0:
                received_data = ser.readline().decode().rstrip()
                ser.write(0)

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
        await message.reply(embed=embed, mention_author=True)

        print("센서정보 데이터 전송완료!\n")

    if message.content == '화분아 급수내역':
        print("급수내역 요청 명령어 입력")

        global waterHistories

        embed = discord.Embed(description=f'', timestamp=datetime.datetime.now(pytz.timezone('UTC')),
                              colour=0x8ACA5C)
        embed.set_author(name=f"{message.author.name} 님의 급수내역 요청", icon_url=message.author.avatar)

        if len(waterHistories) == 0:
            embed.add_field(name=f"급수내역 없음", value=f">>> 수분을 공급한 내역이 없습니다.", inline=False)
        else:
            for i, waterHistory in enumerate(waterHistories[-min(5, len(waterHistories)):]):
                month = waterHistory.month
                day = waterHistory.day
                hour = waterHistory.hour
                minute = waterHistory.minute
                second = waterHistory.second
                embed.add_field(name=f"내역{i + 1}", value=f">>> {month}월 {day}일 {hour}시 {minute}분 {second}초", inline=False)

        embed.set_footer(text=dev)
        await message.reply(embed=embed, mention_author=True)

        print("급수내역 데이터 전송완료!\n")

# 봇 실행
client.run('MTExMDQ3OTY3MDI2NjMwNjY2MA.GuS0oE.ZS8txrY6XMpMJbUBfgj3R0YSAsT1VUMWhXnKow')
