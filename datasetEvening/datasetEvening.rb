def numFiles()
    numFiles = []
    labels = Dir.glob("*")
    labels.each do |i|
        Dir.chdir(i)
        numFiles << Dir.glob("*").count
        Dir.chdir("..")
    end

    return numFiles.min()
end

def datasetEvening(mapp)
    Dir.chdir(mapp)
    targetFiles = numFiles()

    labels = Dir.glob("*")
    labels.each do |i|
        p i
        Dir.chdir(i)
        while Dir.glob("*").count > targetFiles
            i = Dir.glob("*")
            len = i.length-1
            File.delete(i[rand(0..len)])
        end
        Dir.chdir("..")
    end
end

datasetEvening("datasets")