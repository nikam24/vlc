/*****************************************************************************
 * SegmentTemplate.cpp: Implement the UrlTemplate element.
 *****************************************************************************
 * Copyright (C) 1998-2007 VLC authors and VideoLAN
 * $Id$
 *
 * Authors: Hugo Beauzée-Luyssen <hugo@beauzee.fr>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#ifndef SEGMENTTEMPLATE_H
#define SEGMENTTEMPLATE_H

#include "Segment.h"
#include "../tools/Properties.hpp"
#include "SegmentBaseType.hpp"

namespace adaptive
{
    namespace playlist
    {
        class ICanonicalUrl;
        class SegmentTemplateInit;
        class SegmentInformation;
        class SegmentTemplate;

        class SegmentTemplateSegment : public Segment
        {
            public:
                SegmentTemplateSegment( ICanonicalUrl * = nullptr );
                virtual ~SegmentTemplateSegment();
                virtual void setSourceUrl( const std::string &url ); /* reimpl */
                void setParentTemplate( SegmentTemplate * );

            protected:
                const SegmentTemplate *templ;
        };

        class SegmentTemplate : public AbstractMultipleSegmentBaseType
        {
            public:
                SegmentTemplate( SegmentTemplateSegment *, SegmentInformation * = nullptr );
                virtual ~SegmentTemplate();
                void setSourceUrl( const std::string &url );
                uint64_t getLiveTemplateNumber(mtime_t, bool = true) const;
                void pruneByPlaybackTime(mtime_t);
                size_t pruneBySequenceNumber(uint64_t);

                virtual mtime_t getMinAheadTime(uint64_t curnum) const; /* impl */
                virtual Segment * getMediaSegment(uint64_t number) const; /* impl */
                virtual Segment * getNextMediaSegment(uint64_t, uint64_t *, bool *) const; /* impl */
                virtual InitSegment *getInitSegment() const;/* reimpl */
                virtual uint64_t getStartSegmentNumber() const; /* impl */

                virtual bool getSegmentNumberByTime(mtime_t time, uint64_t *ret) const; /* impl */
                virtual bool getPlaybackTimeDurationBySegmentNumber(uint64_t number,
                                            mtime_t *time, mtime_t *duration) const; /* impl */

                virtual void debug(vlc_object_t *, int = 0) const; /* reimpl */

            protected:
                SegmentInformation *parentSegmentInformation;
                SegmentTemplateSegment *virtualsegment;
        };

        class SegmentTemplateInit : public InitSegment
        {
            public:
                SegmentTemplateInit( SegmentTemplate *, ICanonicalUrl * = nullptr );
                virtual ~SegmentTemplateInit();
                virtual void setSourceUrl( const std::string &url ); /* reimpl */

            protected:
                const SegmentTemplate *templ;
        };
    }
}
#endif // SEGMENTTEMPLATE_H
