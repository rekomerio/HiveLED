import json

with open("../hive-host/lib/LEDEffect/ColorPalettes.cpp", 'r') as f:
    index = 0
    isInPaletteList = False
    foundPalettes = []
    usedPalettes = []
    jsonObject = ""
    for line in f:
        line = line.strip()

        if line.find("DEFINE_GRADIENT_PALETTE(") != -1:
            start = line.find("(") + 1
            end = line.find(")")
            isUnique = True
            for palette in foundPalettes:
                if line[start:end] == palette:
                    isUnique = False
                    #print("duplicate: " + str(line[start:end]))      

            if isUnique:
                foundPalettes.append(line[start:end])
                print(line[start:end] + ",")

        if (isInPaletteList):
            if line.find(',') != -1:
                line = line.split(",")[0]
            if line.find('}') != -1: 
                line = line.split('}')[0]
                isInPaletteList = False
            for palette in foundPalettes:
                if palette == line:
                    usedPalettes.append(line)
                    jsonLine = json.dumps({ "name": palette, "value": index })
                    index = index + 1

                    if len(foundPalettes) > index:
                        jsonObject += jsonLine + ",\n"
                    else:
                        jsonObject += jsonLine + "\n"

        if (line.find("hiveColorPalettes[]") != -1):
            isInPaletteList = True

    with open("palettes.json", "w") as file:
        file.write('[\n' + jsonObject + ']')
        file.close()