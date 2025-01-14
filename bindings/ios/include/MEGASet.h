/**
 * @file MEGASet.h
 * @brief Represents a MEGASet in MEGA
 *
 * It allows to get all data related to a Set in MEGA.
 *
 * (c) 2022- by Mega Limited, Auckland, New Zealand
 *
 * This file is part of the MEGA SDK - Client Access Engine.
 *
 * Applications using the MEGA API must present a valid application key
 * and comply with the the rules set forth in the Terms of Service.
 *
 * The MEGA SDK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * @copyright Simplified (2-clause) BSD License.
 *
 * You should have received a copy of the license along with this
 * program.
 */

#import <Foundation/Foundation.h>

typedef NS_ENUM (NSInteger, MEGASetChangeType) {
    MEGASetChangeTypeNew       = 0,
    MEGASetChangeTypeName      = 1,
    MEGASetChangeTypeCover     = 2,
    MEGASetChangeTypeRemoved   = 3,
    MEGASetChangeTypeExported  = 4
};

typedef NS_OPTIONS (NSUInteger, MEGASetChanges) {
    MEGASetChangesNew           = 1 << MEGASetChangeTypeNew,
    MEGASetChangesName          = 1 << MEGASetChangeTypeName,
    MEGASetChangesCover         = 1 << MEGASetChangeTypeCover,
    MEGASetChangesRemoved       = 1 << MEGASetChangeTypeRemoved,
    MEGASetChangesExported      = 1 << MEGASetChangeTypeExported
};

NS_ASSUME_NONNULL_BEGIN

/**
 * @brief Represents a Set in MEGA
 *
 * It allows to get all data related to a Set in MEGA.
 *
 * Objects of this class aren't live, they are snapshots of the state of a Set
 * in MEGA when the object is created, they are immutable.
 *
 */
@interface MEGASet : NSObject

/**
 * @brief Returns id of current Set.
 *
 * @return Set id.
 */
@property (readonly, nonatomic) uint64_t handle;

/**
 * @brief Returns id of user that owns current Set.
 *
 * @return user id.
 */
@property (readonly, nonatomic) uint64_t userId;

/**
 * @brief Returns public id of current Set if it was exported. INVALID_HANDLE otherwise
 *
 * @return Public id of Set.
 */
@property (readonly, nonatomic) uint64_t publicId;

/**
 * @brief Returns id of Element set as 'cover' for current Set.
 *
 * It will return INVALID_HANDLE if no cover was set or if the Element became invalid
 * (was removed) in the meantime.
 *
 * @return Element id.
 */
@property (readonly, nonatomic) uint64_t cover;

/**
 * @brief Returns timestamp of latest changes to current Set (but not to its Elements).
 *
 * @return timestamp value.
 */
@property (readonly, nonatomic) NSDate *timestamp;

/**
 * @brief Returns creation timestamp of current Set.
 *
 * @return timestamp value.
 */
@property (readonly, nonatomic) NSDate *timestampCreated;

/**
 * @brief Returns name of current Set.
 *
 * @return name of current Set.
 */
@property (readonly, nonatomic, nullable) NSString *name;

/**
 * @brief Returns YES if this Set has a specific change
 *
 * This value is only useful for Sets notified by [MEGADelegate onSetsUpdate:sets:]  or
 * [MEGAGlobalDelegate onSetsUpdate:sets:] that can notify about Set modifications.
 *
 * In other cases, the return value of this function will be always false.
 *
 * @param changeType The type of change to check. It can be one of the following values:
 *
 * - MEGASetChangeTypeNew                  = 0
 * Check if the Set was new
 *
 * - MEGASetChangeTypeName                = 1
 * Check if Set name has changed
 *
 * - MEGASetChangeTypeCover                = 2
 * Check if Set cover has changed
 *
 * - MEGASetChangeTypeRemoved          = 3
 * Check if the Set was removed
 *
 * - MEGASetChangeTypeExported           = 4
 * Check if the Set was exported or disabled (i.e. exporting ended)
 *
 * @return YES if this Set has a specific change
 */
- (BOOL)hasChangedType:(MEGASetChangeType)changeType;

/**
 * @brief Returns changes  for MEGASet
 *
 * Note that the position of each bit matches the MEGASetChangeType value
 *
 * @return combination of changes in
 */
- (MEGASetChanges)changes;

/**
 * @brief Returns true if this Set is exported (can be accessed via public link)
 *
 * Public link is retrieved when the Set becomes exported
 *
 * @return true if this Set is exported
 */
- (BOOL)isExported;

@end

NS_ASSUME_NONNULL_END
