import xml.etree.ElementTree as ET
import sys



root = ET.parse(sys.argv[1]).getroot()


def getFrequency(note):
    notes = ['A', 'A#', 'B', 'C', 'C#', 'D', 'D#', 'E', 'F', 'F#', 'G', 'G#']

    if len(note) == 3:
        octave = int(note[2])
    else:
        octave = int(note[1])

    keyNumber = notes.index(note[:len(note)-1])

    if keyNumber < 3:
        keyNumber = keyNumber + 12 + ((octave - 1) * 12) + 1
    else:
        keyNumber = keyNumber + ((octave - 1) * 12) + 1

    return int(440 * (2 ** ((keyNumber - 49) / 12)))



noteLength = {
    "full": 1.0,
    "half": 1/2,
    "quarter": 1/4,
    "eighth": 1/8,
    "16th": 1/16,
    "32nd": 1/32,
    "64th": 1/64
}


for part in root.findall('part'):
    print(part.attrib['id'])
    perMinute = part.find('.//per-minute')
    bpm = 120
    if perMinute is not None:
        bpm = int(part.find('.//per-minute').text)
    
    print(bpm, "bpm")

    time = part.find('.//time')
    beats = int(time.find('beats').text)
    beatType = int(time.find('beat-type').text)

    fullTime = 1 / (bpm / beatType / 60) * 1000  # in ms

    print(beats, beatType, fullTime)
    

    def getDuration(note):
        try:
            if note.find('rest').attrib['measure'] == 'yes':
                return beats * fullTime
        except:
            pass

        noteDuration = fullTime * noteLength[note.find('type').text]
        if note.find('dot') is not None:
            return noteDuration + noteDuration / 2
        return noteDuration


    tieTime = 0
    
    for measure in part.findall('measure'):
        for note in measure.findall('note'):

            noteDuration = int(getDuration(note))

            tie = note.findall('tie')

            if len(tie) > 0 :
                if len(tie) == 1:
                    if tie[0].attrib['type'] == 'start':
                        tieTime = noteDuration
                        continue
                    if tie[0].attrib['type'] == 'stop':
                        noteDuration = noteDuration + tieTime
                else:
                    tieTime = tieTime + noteDuration
                    continue


            pitch = note.find('pitch')

            

            accidental = getattr(note.find('accidental'), "text", None)

            if note.find('rest') is not None:
                print('{0, ' + str(noteDuration)+'},')
            else:
                noteString = pitch.find('step').text+pitch.find('octave').text
                if accidental == 'sharp':
                    noteString = pitch.find(
                        'step').text+'#'+pitch.find('octave').text
                print('{' + str(getFrequency(noteString)) +
                      ', ' + str(noteDuration)+'},')
