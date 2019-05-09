#include "tagsource.h"
#include "taglib/tag.h"
#include "taglib/fileref.h"
#include "taglib/mpegfile.h"
#include <taglib/id3v2tag.h>
#include <taglib/id3v2frame.h>
#include <taglib/id3v2header.h>
#include <taglib/attachedpictureframe.h>

#include <QCryptographicHash>
#include <QDir>

#include <QDebug>

TagSource::TagSource(QObject *parent) : QObject(parent)
{
    QDir().mkpath("./buffered/");
}

QMap<QString, QVariant> TagSource::getTagsFromFile(const QString &filename)
{
    QMap<QString, QVariant> tags;

    if(!QFile::exists(filename)) {
        tags["filename"] = "-";
        return tags;
    }

//    tags["filename"] = filename;
//    tags["genres"] = "";
//    tags["artistName"] = "";
//    tags["albumTitle"] = "";
//    tags["trackNum"] = 0;
//    tags["trackName"] = filename.section('/', -1);

    TagLib::FileRef f(QByteArray().append(filename));
    TagLib::Tag *fileTags = f.tag();

    tags["filename"] = filename;
    tags["genres"] = fileTags->genre().toCString(true);
    tags["artistName"] = fileTags->artist().toCString(true);
    tags["albumTitle"] = fileTags->album().toCString(true);
    tags["trackNum"] = fileTags->track();
    tags["trackName"] = fileTags->title().toCString(true);
    tags["cover"] = "";

    static const char *IdPicture = "APIC";
    TagLib::MPEG::File mpegFile(QByteArray().append(filename));
    TagLib::ID3v2::Tag *id3v2tag = mpegFile.ID3v2Tag();

    if(id3v2tag) {
        TagLib::ID3v2::FrameList Frame = id3v2tag->frameListMap()[IdPicture] ;
        if (!Frame.isEmpty() ) {
            for(TagLib::ID3v2::FrameList::ConstIterator it = Frame.begin(); it != Frame.end(); ++it) {
                TagLib::ID3v2::AttachedPictureFrame *PicFrame = (TagLib::ID3v2::AttachedPictureFrame *)(*it) ;

                TagLib::ByteVector datVector = PicFrame->picture();

                QByteArray data = QByteArray(datVector.data(), datVector.size());
                QString coverName = QCryptographicHash::hash(data, QCryptographicHash::Md5).toBase64(QByteArray::Base64UrlEncoding | QByteArray::OmitTrailingEquals);

                QFile file("./buffered/" + coverName);
                if(!file.exists()) {
                    file.open(QIODevice::WriteOnly);
                    file.write(data);
                    file.close();
                }

                tags["cover"] = coverName;
            }

        }

    }

    return tags;
}
