import mido

tick_in_beat = 480
notelen_0 = tick_in_beat * 8
notelen_1 = tick_in_beat * 4
notelen_2 = tick_in_beat * 2
notelen_4 = tick_in_beat
notelen_8 = tick_in_beat // 2
notelen_16 = tick_in_beat // 4
notelen_32 = tick_in_beat // 8

A1, Bb1, B1 = 21, 22, 23

C1, Db1, D1, Eb1, E1, F1, Gb1, G1, Ab2, A2, Bb2, B2 \
    = 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35

C2, Db2, D2, Eb2, E2, F2, Gb2, G2, Ab3, A3, Bb3, B3 \
    = 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47

C3, Db3, D3, Eb3, E3, F3, Gb3, G3, Ab4, A4, Bb4, B4 \
    = 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59

C4, Db4, D4, Eb4, E4, F4, Gb4, G4, Ab5, A5, Bb5, B5 \
    = 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71

C5, Db5, D5, Eb5, E5, F5, Gb5, G5, Ab6, A6, Bb6, B6 \
    = 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83

C6, Db6, D6, Eb6, E6, F6, Gb6, G6, Ab7, A7, Bb7, B7 \
    = 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95

C7, Db7, D7, Eb7, E7, F7, Gb7, G7, Ab7, A8, Bb8, B8 \
    = 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107

C8 = 108

righthand = (B5, C5, D5, E5, F5, G5, A6, B6, C6, D6)
lefthand = (B3, C3, D3, E3, F3, G3, A4, B4, C4, D4)

mid1 = mido.MidiFile()

def trackedit(track_program, track_velocity, track_name, filepath, isrighthand):
    str_file = open(filepath)
    str = str_file.read()
    str = "".join(str.split())
    print(str)
    str_file.close()

    track_editing = mido.MidiTrack()
    track_editing.append(mido.Message("program_change", program = track_program, time = 0))
    track_editing.append(mido.MetaMessage("track_name", name = track_name, time = 0)) # 音轨名
    track_editing.append(mido.MetaMessage("time_signature", numerator = 4, denominator = 4, time = 0)) # 拍号
    track_editing.append(mido.MetaMessage("key_signature", key = "C", time = 0)) # 调号
    track_editing.append(mido.MetaMessage("set_tempo", tempo = 375000, time = 0)) # 60,000,000uspm / 160bpm

    len = notelen_0
    empty_len = 0

    for i in str:
        i_note = C4
        if i == ".":
            len = notelen_16
            empty_len = notelen_1
            continue
        elif isrighthand == True:
            i_note = righthand[int(i)]
        else:
            i_note = lefthand[int(i)]

        track_editing.append(mido.Message("note_on", note = i_note, velocity = track_velocity, time = empty_len))
        track_editing.append(mido.Message("note_off", note = i_note, velocity = track_velocity, time = len))

        empty_len = 0

    mid1.tracks.append(track_editing)

trackedit(0, 100, "Track 1", "pstr.txt", True) # 0 = Acoustic Grand Piano
trackedit(0, 100, "Track 2", "estr.txt", False)
mid1.save("mid1.mid")
