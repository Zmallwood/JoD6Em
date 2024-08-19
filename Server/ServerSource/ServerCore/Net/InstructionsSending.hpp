/*
 * InstructionsSending.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

///
/// Send an image drawing instruction to the user.
///
/// @param userID User ID of user for which to draw.
/// @param imageName Name of image to draw.
/// @param dest Destination to draw the image at.
///
void UserSendDrawImage(
    UserID userID,
    std::string_view imageName,
    BoxF dest);

///
/// Send an image drawing instruction to the user.
///
/// @param userID User ID of user for which to draw.
/// @param imageNamehash Hash code of image name to draw.
/// @param dest Destination to draw the image at.
///
void UserSendDrawImage(
    UserID userID,
    int imageNamehash,
    BoxF dest);

void UserSendDrawImageRepeated(
    UserID userID, std::string_view imageName,
    BoxF dest, SizeF textureFillAmount);

///
/// Send a text drawing instruction to the user.
///
/// @param userID User ID of user for which to draw.
/// @param text Text to draw.
/// @param position Position to draw the text at.
/// @param centerAlign
///
void UserSendDrawText(
    UserID userID,
    std::string_view text, PointF position, bool centerAlign = false);

///
/// Send instruction to present canvas to the user.
///
/// @param userID User ID of user for which to present canvas.
///
void UserSendPresentCanvas(UserID userID);

///
/// Send request to user to retrieve dimensions for an image.
///
/// @param userID User ID of user for which to request image dimensions.
/// @param imageNameHash Hash code of image name to get dimensions for.
///
void UserSendReqImageDimensions(
    UserID userID,
    int imageNameHash);

///
/// Send request to user to retrieve dimensions for an image.
///
/// @param userID User ID of user for which to request image dimensions.
/// @param imageNameHash Hash code of image name to get dimensions for.
///
void UserSendReqImageDimensions(
    UserID userID,
    std::string_view imageName);

}