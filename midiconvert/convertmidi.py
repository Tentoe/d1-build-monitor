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
    "half": 0.5,
    "quarter": 0.25,
    "eighth": 0.125,
    "16th": 0.0625,
    "32th": 0.03125,
}


for part in root.findall('part'):
    print(part.attrib['id'])
    bpm = int(part.find('.//per-minute').text)
    print(bpm, "bpm")

    time = part.find('.//time')
    beats = int(time.find('beats').text)
    beatType = int(time.find('beat-type').text)

    fullTime = 1 / (bpm / beatType / 60) * 1000  # in ms

    print(beats, beatType, fullTime)

    for measure in part.findall('measure'):
        for note in measure.findall('note'):
            pitch = note.find('pitch')

            noteDuration = fullTime * noteLength[note.find('type').text]

            if note.find('dot') is not None:
                noteDuration = noteDuration + noteDuration / 2
            accidental = getattr(note.find('accidental'), "text", None)

            if note.find('rest') is not None:
                print('{0, ' + str(int(noteDuration))+'},')
            else:
                noteString = pitch.find('step').text+pitch.find('octave').text
                if accidental == 'sharp':
                    noteString = pitch.find(
                        'step').text+'#'+pitch.find('octave').text
                print('{' + str(getFrequency(noteString)) +
                      ', ' + str(int(noteDuration))+'},')
