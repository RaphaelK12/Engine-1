#include "GraphicsTypesPch.h"
#include "GraphicsTypes/GraphicsSceneView.h"

#include "Rendering/Renderer.h"
#include "Rendering/RConstantBuffer.h"
#include "Rendering/RRenderContext.h"
#include "Rendering/RSurface.h"

using namespace Helium;

const float32_t GraphicsSceneView::DEFAULT_HORIZONTAL_FOV = 70.0f;
const float32_t GraphicsSceneView::DEFAULT_ASPECT_RATIO = 1.0f;
const float32_t GraphicsSceneView::DEFAULT_NEAR_CLIP = 0.5f;
const float32_t GraphicsSceneView::DEFAULT_FAR_CLIP = -1.0f;
const float32_t GraphicsSceneView::DEFAULT_SHADOW_CUTOFF_DISTANCE = 1500.0f;
const float32_t GraphicsSceneView::DEFAULT_SHADOW_FADE_DISTANCE = 1000.0f;

/// Constructor.
GraphicsSceneView::GraphicsSceneView()
	: m_viewMatrix( Simd::Matrix44::IDENTITY )
	, m_projectionMatrix( Simd::Matrix44::IDENTITY )
	, m_inverseViewMatrix( Simd::Matrix44::IDENTITY )
	, m_inverseViewProjectionMatrix( Simd::Matrix44::IDENTITY )
	, m_origin( 0.0f )
	, m_forward( 0.0f, 0.0f, 1.0f )
	, m_up( 0.0f, 1.0f, 0.0f )
	, m_clearColor( 0 )
	, m_viewportX( 0 )
	, m_viewportY( 0 )
	, m_viewportWidth( 0 )
	, m_viewportHeight( 0 )
	, m_horizontalFov( DEFAULT_HORIZONTAL_FOV )
	, m_aspectRatio( DEFAULT_ASPECT_RATIO )
	, m_nearClip( DEFAULT_NEAR_CLIP )
	, m_farClip( DEFAULT_FAR_CLIP )
	, m_shadowCutoffDistance( DEFAULT_SHADOW_CUTOFF_DISTANCE )
	, m_shadowFadeDistance( DEFAULT_SHADOW_FADE_DISTANCE )
	, m_bDirtyView( true )
{
	MemoryZero( &m_frustum, sizeof( m_frustum ) );
}

/// Set the render context that should be used by this view.
///
/// @param[in] pRenderContext  Render context to assign.
///
/// @see SetDepthStencilSurface(), SetViewport(), GetRenderContext(), GetDepthStencilSurface(), GetViewportX(),
///      GetViewportY(), GetViewportWidth(), GetViewportHeight()
void GraphicsSceneView::SetRenderContext( RRenderContext* pRenderContext )
{
	m_spRenderContext = pRenderContext;
}

/// Set the depth-stencil surface for this view to use.
///
/// @param[in] pSurface  Depth-stencil surface to use.
///
/// @see SetRenderContext(), SetViewport(), GetDepthStencilSurface(), GetRenderContext(), GetViewportX(),
///      GetViewportY(), GetViewportWidth(), GetViewportHeight()
void GraphicsSceneView::SetDepthStencilSurface( RSurface* pSurface )
{
	m_spDepthStencilSurface = pSurface;
}

/// Set the viewport dimensions for this view to use.
///
/// @param[in] x       Horizontal pixel coordinate of the upper-left viewport corner.
/// @param[in] y       Vertical pixel coordinate of the upper-left viewport corner.
/// @param[in] width   Viewport width, in pixels.
/// @param[in] height  Viewport height, in pixels.
///
/// @see SetRenderContext(), SetDepthStencilSurface(), GetViewportX(), GetViewportY(), GetViewportWidth(),
///      GetViewportHeight(), GetRenderContext(), GetDepthStencilSurface()
void GraphicsSceneView::SetViewport( uint32_t x, uint32_t y, uint32_t width, uint32_t height )
{
	m_viewportX = x;
	m_viewportY = y;
	m_viewportWidth = width;
	m_viewportHeight = height;
}

/// Set the color to which the viewport color buffer should be filled at the start of each frame.
///
/// @param[in] rColor  Clear color.
///
/// @see GetClearColor()
void GraphicsSceneView::SetClearColor( const Color& rColor )
{
	m_clearColor = rColor;
}

/// Set the view origin and orientation.
///
/// @param[in] rOrigin   View origin.
/// @param[in] rForward  View direction.
/// @param[in] rUp       Up direction.
///
/// @see SetHorizontalFov(), SetAspectRatio()
void GraphicsSceneView::SetView( const Simd::Vector3& rOrigin, const Simd::Vector3& rForward, const Simd::Vector3& rUp )
{
	m_origin = rOrigin;
	m_forward = rForward;
	m_up = rUp;

	m_bDirtyView = true;
}

/// Set the horizontal field-of-view angle.
///
/// @param[in] fov  Field-of-view angle, in degrees.
///
/// @see SetView(), SetAspectRatio()
void GraphicsSceneView::SetHorizontalFov( float32_t fov )
{
	m_horizontalFov = Clamp( fov, 0.0f, 180.0f );

	m_bDirtyView = true;
}

/// Set the aspect ratio.
///
/// @param[in] aspectRatio  Aspect ratio (width to height).
///
/// @see SetView(), SetHorizontalFov()
void GraphicsSceneView::SetAspectRatio( float32_t aspectRatio )
{
	HELIUM_ASSERT( aspectRatio >= HELIUM_EPSILON );
	m_aspectRatio = Max( aspectRatio, HELIUM_EPSILON );

	m_bDirtyView = true;
}

/// Set the near clip plane distance.
///
/// @param[in] distance  Near clip distance.
///
/// @see SetFarClip()
void GraphicsSceneView::SetNearClip( float32_t distance )
{
	HELIUM_ASSERT( distance >= HELIUM_EPSILON );
	m_nearClip = Max( distance, HELIUM_EPSILON );

	m_bDirtyView = true;
}

/// Set the far clip plane distance.
///
/// @param[in] distance  Far clip plane distance, or a value less than zero to use an infinite far clip plane.
///
/// @see SetNearClip()
void GraphicsSceneView::SetFarClip( float32_t distance )
{
	HELIUM_ASSERT( distance >= HELIUM_EPSILON || distance < 0.0f );
	m_farClip = ( distance < 0.0f ? distance : Max( distance, HELIUM_EPSILON ) );

	m_bDirtyView = true;
}

/// Update the various view- and projection-related transform matrices from the view settings if necessary.
void GraphicsSceneView::UpdateViewProjection()
{
	// Don't update the transform matrices if the view parameters are not dirty.
	if( !m_bDirtyView )
	{
		return;
	}

	m_bDirtyView = false;

	// Compute the projection matrix.
	if ( m_horizontalFov < HELIUM_EPSILON )
	{
		m_projectionMatrix.SetOrthographicProjection( static_cast<float>(m_viewportWidth), static_cast<float>(m_viewportHeight), m_nearClip, m_farClip);
	}
	else
	{
		float32_t horizontalFovRadians = m_horizontalFov * static_cast< float32_t >( HELIUM_DEG_TO_RAD );
		if( m_farClip >= 0.0f )
		{
			m_projectionMatrix.SetPerspectiveProjection( horizontalFovRadians, m_aspectRatio, m_nearClip, m_farClip );
		}
		else
		{
			m_projectionMatrix.SetPerspectiveProjection( horizontalFovRadians, m_aspectRatio, m_nearClip );
		}
	}

	// Orthonormalize the view basis and compute the view matrix.
	Simd::Vector3 forward = m_forward.GetNormalized();

	Simd::Vector3 right;
	right.CrossSet( m_up, forward );
	right.Normalize();

	Simd::Vector3 up;
	up.CrossSet( forward, right );

	m_viewMatrix = Simd::Matrix44(
		right.GetElement( 0 ),    right.GetElement( 1 ),    right.GetElement( 2 ),    0.0f,
		up.GetElement( 0 ),       up.GetElement( 1 ),       up.GetElement( 2 ),       0.0f,
		forward.GetElement( 0 ),  forward.GetElement( 1 ),  forward.GetElement( 2 ),  0.0f,
		m_origin.GetElement( 0 ), m_origin.GetElement( 1 ), m_origin.GetElement( 2 ), 1.0f );

	// Compute the inverse view and combined inverse view/projection matrices.
	m_viewMatrix.GetInverse( m_inverseViewMatrix );
	m_inverseViewProjectionMatrix.MultiplySet( m_inverseViewMatrix, m_projectionMatrix );

	// Initialize the view frustum.
	m_frustum.Set( m_inverseViewProjectionMatrix.GetTranspose() );
}
