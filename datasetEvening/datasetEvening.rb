def numFiles()
    numFiles = []
    labels = Dir.glob("*")
    labels.each do |i|
        Dir.chdir(i)
        fileCount = Dir.glob("*").count
        if fileCount != 0
            numFiles << fileCount
            Dir.chdir("..")
        else
            Dir.chdir("..")
            Dir.rmdir(i)
        end
    end

    return numFiles.min()
end

def datasetEvening(mapp)
    Dir.chdir(mapp)
    targetFiles = numFiles()
    
    labels = Dir.glob("*")
    labels.each do |i|
        Dir.chdir(i)
        while Dir.glob("*").count > targetFiles
            i = Dir.glob("*")
            len = i.length-1
            File.delete(i[rand(0..len)])
        end
        p i + ": Done"
        Dir.chdir("..")
    end
end

datasetEvening("datasets")